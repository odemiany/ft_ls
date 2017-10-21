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
	t_files *ptr;
	int ret;

	ptr = s_info->unsorted;
	while (ptr != NULL)
	{
		ret = is_dir(ptr->file);
		if (ret == 1)
			ft_putstr("dir!\n");
		//	add_to_dir(ptr->file);
		else if (ret == 0)
			ft_putstr("not_dir\n");
		//	add_to_not_dir(ptr->file);
		ptr = ptr->next;
	}
	//free_list(s_info->unsorted);
}

int		is_dir(char *filename)
{
	DIR *dir;

	dir = opendir(filename);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	if (errno == ENOTDIR)
		return (0);
	else if (errno == ENOENT)
	{
		ft_putstr("ls: ");
		ft_putstr(filename);
		ft_putstr(": No such file or directory\n");
	}
	else if (errno == EACCES)
	{
		ft_putstr("ls: ");
		ft_putstr(filename);
		ft_putstr(": Permission denied\n");
	}
	return (-1);
}