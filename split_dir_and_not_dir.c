/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dir_and_not_dir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 22:10:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/21 22:10:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	split_dir_and_not_dir(t_ls_struct *s_info)
{
	t_files			*ptr;
	int				ret;

	s_info->not_dir = NULL;
	s_info->dir = NULL;
	ptr = s_info->unsorted;
	while (ptr != NULL)
	{
		ret = is_dir(ptr->file);
		if (ret == 1)
			add_to_dir(ptr->file, s_info);
		else if (ret == 0)
			check_for_soft_link(ptr->file, s_info);
		ptr = ptr->next;
	}
	sort_input_params(s_info);
	free_list(s_info->unsorted);
}

int		is_dir(char *filename)
{
	DIR				*dir;
	struct stat		buf;

	dir = opendir(filename);
	if (dir != NULL)
	{
		closedir(dir);
		lstat(filename, &buf);
		if (S_ISLNK(buf.st_mode) != 0)
			return (0);
		return (1);
	}
	if (errno == ENOTDIR)
		return (0);
	err_mgmt(filename);
	return (-1);
}

void	add_to_dir(char *str, t_ls_struct *s_info)
{
	t_files	*tmp;

	if (s_info->dir == NULL)
	{
		s_info->dir = (t_files *)malloc(sizeof(t_files));
		s_info->dir->prev = NULL;
		s_info->dir->next = NULL;
		s_info->dir->file = ft_strdup(str);
		return ;
	}
	tmp = s_info->dir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_files *)malloc(sizeof(t_files));
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
	tmp->next->file = ft_strdup(str);
}

void	add_to_not_dir(char *str, t_ls_struct *s_info)
{
	t_files	*tmp;

	if (s_info->not_dir == NULL)
	{
		s_info->not_dir = (t_files *)malloc(sizeof(t_files));
		s_info->not_dir->prev = NULL;
		s_info->not_dir->next = NULL;
		s_info->not_dir->file = ft_strdup(str);
		return ;
	}
	tmp = s_info->not_dir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_files *)malloc(sizeof(t_files));
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
	tmp->next->file = ft_strdup(str);
}

void	check_for_soft_link(char *filename, t_ls_struct *s_info)
{
	struct stat		buf;

	lstat(filename, &buf);
	if (S_ISLNK(buf.st_mode) != 0)
	{
		if (ft_strchr(s_info->flags, 'l') == NULL)
		{
			if (filename[ft_strlen(filename) - 1] == '/')
				add_to_dir(filename, s_info);
			else
				add_to_not_dir(filename, s_info);
		}
		else
			add_to_not_dir(filename, s_info);
	}
	else
			add_to_not_dir(filename, s_info);
}
