/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 19:05:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/22 19:05:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_flag(int not_dir_exists, size_t elem_count)
{
	if (not_dir_exists == 0 && elem_count == 1)
		return (0);
	else
		return (1);
}

void	operate_dir(t_ls_struct *s_info)
{
	t_files	*list;
	char	*path;

	list = s_info->dir;
	if (list == NULL)
		return ;
	path = "\0";
	s_info->n_flag = count_flag(s_info->not_dir_exists, count_elem(list));
	while (list != NULL)
	{
		path = ft_strjoin(path, list->file);
		recursion(path, s_info);
		((list = list->next) == NULL) ? 0 : write(1, "\n", 1);
	}
	free_list(s_info->dir);
}

void	recursion(char *fold_name, t_ls_struct *s_info)
{
	t_files	*file;
	t_files	*file_cp;
	char	*t_name;

	(s_info->n_flag == 0) ? s_info->n_flag = 1 : write_fold_name(fold_name);
	file = NULL;
	read_folder(fold_name, &file, s_info->flags);
	apply_sorting(s_info->flags, file, &file, fold_name);
	print_folder(file, s_info, fold_name);
	if (ft_strchr(s_info->flags, 'R') != NULL)
	{
		file_cp = file;
		while (file_cp != NULL)
		{
			if (is_dot(file_cp->file))
				continue ;
			t_name = make_next_name(fold_name, file_cp->file);
			if (is_dot(file_cp->file) == 1)
				continue ;
			(is_dir(t_name) == 1) ? recursion(t_name, s_info) : free(t_name);
			file_cp = file_cp->next;
		}
	}
	free(fold_name);
	free_list(file);
}

char 	*make_next_name(char *fold_name, char *file_name)
{
	char	*tmp;
	char	*ret;

	ret = ft_strjoin(fold_name, "/");
	tmp = ret;
	ret = ft_strjoin(ret, file_name);
	free(tmp);
	return (ret);
}

void	apply_sorting(char *flags, t_files *file, t_files **file_ptr,
																char *fold_name)
{
	if (ft_strchr(flags, 't') != NULL)
	{
		get_mtime(file, fold_name);
		sort_list(file, BY_TIME, file_ptr);
	}
	else
		sort_list(file, LEXICOGRAPHIC, file_ptr);
	if (ft_strchr(flags, 'r') != NULL)
		sort_list(file, REVERSE, file_ptr);
}

void	write_fold_name(char *str)
{
		ft_putstr("\n");
		ft_putstr(str);
		ft_putendl(":");
}

void	read_folder(char *folder, t_files **file, char *flags)
{
	DIR 		*dir;
	t_dirent	*ent;

	dir = opendir(folder);
	if (dir == NULL)
	{
		err_mgmt(folder);
		return ;
	}
	while ((ent = readdir(dir)) != NULL)
	{
		if (ft_strchr(flags, 'a') == NULL && ent->d_name[0] == '.')
			continue ;
		add_to_list(ent->d_name, *file, file);
	}
	if (ft_strchr(flags, 'l') != NULL)
		write(1, "", 1);
		//get_extend_data(*file);
	closedir (dir);
}

void	print_folder(t_files *file, t_ls_struct *s_info, char *fold_name)
{
	if (ft_strchr(s_info->flags, 'l') == NULL)
		print_simple_folder(file);
	else
		print_extend_folder(file, fold_name);
}

void	err_mgmt(char *str)
{
	ft_putstr("ls: ");
	perror(str);
}

void	get_mtime(t_files *list, char *fold_name)
{
	t_stat	file_info;
	char	*full_name;

	if (list == NULL)
		return ;
	while (list != NULL)
	{
		full_name = make_next_name(fold_name, list->file);
		lstat(full_name, &file_info);
		list->mtime = file_info.st_mtimespec.tv_sec;
		list->n_mtime = file_info.st_mtimespec.tv_nsec;
		list = list->next;
		free(full_name);
	}
}

int		is_dot(char *filename)
{
	if (filename[0] == '.')
	{
		if (ft_strlen(filename) == 1)
			return (1);
		else if (ft_strlen(filename) == 2 && filename[1] == '.')
			return (1);
	}
	return (0);
}
