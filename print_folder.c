/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_folder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:13:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 04:43:07 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_folder(t_files *file, t_ls_struct *s_info, char *fold_name)
{
	if (ft_strchr(s_info->flags, 'l') == NULL)
		print_simple_folder(file);
	else
		print_extend_folder(file, fold_name);
}

void	print_simple_folder(t_files *file)
{
	if (!file)
		return ;
	while (file != NULL)
	{
		ft_putendl(file->file);
		file = file->next;
	}
}

void	print_extend_folder(t_files *file, char *fold_name)
{
	char		*fullname;
	t_files		*file_cp;
	t_stat		file_info;

	if (!file)
		return ;
	count_total_blocks(file, fold_name);
	file_cp = file;
	while (file != NULL)
	{
		fullname = make_next_name(fold_name, file->file);
		lstat(fullname, &file_info);
		get_file_type_and_perm(file, &file_info);
		get_acl_and_xattr(file, fullname);
		file->st_nlink = file_info.st_nlink;
		file->uid = ft_strdup(getpwuid(file_info.st_uid)->pw_name);
		file->gid = ft_strdup(getgrgid(file_info.st_gid)->gr_name);
		get_file_size(file, &file_info);
		get_last_modified_time(file, &file_info);
		check_softlink(fullname, file);
		file = file->next;
		free(fullname);
	}
	print_data(file_cp);
}

void	print_data(t_files *file)
{
	t_len	max_len;

	count_max_len(file, &max_len);
	while (file != NULL)
	{
		ft_putstr(file->perm);
		print_space(max_len.link - (long long)count_num(file->st_nlink));
		ft_putnbr(file->st_nlink);
		write(1, " ", 1);
		ft_putstr(file->uid);
		print_space(max_len.uid - ft_strlen(file->uid) + 2);
		ft_putstr(file->gid);
		print_space(max_len.gid - ft_strlen(file->gid) + 2);
		print_size(file, &max_len);
		ft_putstr(file->last_modified);
		(file->perm[0] == 'l') ? print_softlink(file) : ft_putendl(file->file);
		free(file->gid);
		file = file->next;
	}
}

void	count_max_len(t_files *file, t_len *max_len)
{
	size_t tmp_len;

	max_len->uid = 0;
	max_len->gid = 0;
	max_len->size = 0;
	max_len->link = 0;
	while (file != NULL)
	{
		max_len->uid = (ft_strlen(file->uid) > max_len->uid) ?
										ft_strlen(file->uid) : max_len->uid;
		max_len->gid = (ft_strlen(file->gid) > max_len->gid) ?
										ft_strlen(file->gid) : max_len->gid;
		max_len->link = (count_num((long long)file->st_nlink) > max_len->link) ?
						count_num((long long)file->st_nlink) : max_len->link;
		if (file->special_files_exists == 1)
			tmp_len = count_num(file->major) + count_num(file->minor) + 2;
		else
			tmp_len = count_num(file->size);
		max_len->size = (tmp_len > max_len->size) ? tmp_len : max_len->size;
		file = file->next;
	}
}
