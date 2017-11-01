/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 19:05:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 04:39:44 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	operate_dir(t_ls_struct *s_info)
{
	t_files	*list;
	char	*path;

	list = s_info->dir;
	if (list == NULL)
		return ;
	s_info->n_flag = count_flag(s_info->not_dir_exists, count_elem(list));
	while (list != NULL)
	{
		path = "\0";
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

void	read_folder(char *folder, t_files **file, char *flags)
{
	DIR			*dir;
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
	closedir(dir);
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
