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

void	operate_dir(t_ls_struct *s_info)
{
	t_files	*list;
	t_files	*file;
	size_t	elem_count;

	list = s_info->dir;
	if (list == NULL)
		return;
	file = NULL;
	elem_count = count_elem(list);
	while (list != NULL)
	{
		check_count(elem_count, list->file);
		read_folder(list->file, &file, s_info->flags);
		apply_sorting(s_info->flags, file, &file);
		if (ft_strchr(s_info->flags, 'l') == NULL)
			print_simple_folder(file);
		else
			print_extend_folder(file);
		list = list->next;
		free_list(file);
	}
}

void	apply_sorting(char *flags, t_files *file, t_files **file_ptr)
{
	if (ft_strchr(flags, 'i') != NULL)
		sort_list(file, BY_TIME, file_ptr);
	else
		sort_list(file, LEXICOGRAPHIC, file_ptr);
	if (ft_strchr(flags, 'r') != NULL)
		sort_list(file, REVERSE, file_ptr);
}

void	check_count(size_t i, char *str)
{
	if (i > 1)
	{
		ft_putstr(str);
		ft_putendl(":");
	}
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
		if (ft_strchr(flags, 'a') != NULL && ent->d_name[0] == '.')
		add_to_list(ent->d_name, *file, file);
	}
	if (ft_strchr(flags, 'l') != NULL)
		write(1, "", 1);
		//get_extend_data(*file);
	closedir (dir);
}

void	err_mgmt(char *str)
{
	ft_putstr("ls: ");
	perror(str);
}
