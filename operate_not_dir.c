/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_not_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 18:45:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/22 18:45:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	operate_not_dir(t_ls_struct *s_info)
{
	t_files	*list;

	list = s_info->not_dir;
	if (list == NULL)
	{
		s_info->not_dir_exists = 0;
		return;
	}
	s_info->not_dir_exists = 1;
	while (list != NULL)
	{
		if (ft_strchr(s_info->flags, 'l') == NULL)
			ft_putendl(list->file);
		else
			get_extend_stuff(list);
		list = list->next;
	}
	free_list(s_info->not_dir);

	s_info->dir == NULL ? 0 : write(1, "\n", 1);
}

void	get_extend_stuff(t_files *file)
{
	t_stat		file_info;

	lstat(file->file, &file_info);
	get_file_type_and_perm(file, &file_info);
	get_acl_and_xattr(file, file->file);
	file->st_nlink = file_info.st_nlink;
	file->uid = ft_strdup(getpwuid(file_info.st_uid)->pw_name);
	file->gid = ft_strdup(getgrgid(file_info.st_gid)->gr_name);
	get_file_size(file, &file_info);
	get_last_modified_time(file, &file_info);
	check_softlink(file->file, file);
	print_data(file);
}