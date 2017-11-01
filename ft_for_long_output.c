/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_long_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:08:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 04:32:13 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_file_type_and_perm(t_files *file, t_stat *file_info)
{
	file->perm[0] = get_file_type(file_info);
	if (file_info->st_mode & S_IRUSR)
		file->perm[1] = 'r';
	else
		file->perm[1] = '-';
	if (file_info->st_mode & S_IWUSR)
		file->perm[2] = 'w';
	else
		file->perm[2] = '-';
	if (file_info->st_mode & S_IXUSR)
		file->perm[3] = 'x';
	else
		file->perm[3] = '-';
	if (file_info->st_mode & S_IRGRP)
		file->perm[4] = 'r';
	else
		file->perm[4] = '-';
	if (file_info->st_mode & S_IWGRP)
		file->perm[5] = 'w';
	else
		file->perm[5] = '-';
	permissions_part2(file, file_info);
}

void	permissions_part2(t_files *file, t_stat *file_info)
{
	if (file_info->st_mode & S_IXGRP)
		file->perm[6] = 'x';
	else
		file->perm[6] = '-';
	if (file_info->st_mode & S_IROTH)
		file->perm[7] = 'r';
	else
		file->perm[7] = '-';
	if (file_info->st_mode & S_IWOTH)
		file->perm[8] = 'w';
	else
		file->perm[8] = '-';
	if (file_info->st_mode & S_IXOTH)
		file->perm[9] = 'x';
	else
		file->perm[9] = '-';
}

char	get_file_type(t_stat *file_info)
{
	if (S_ISBLK(file_info->st_mode) > 0)
		return ('b');
	else if (S_ISCHR(file_info->st_mode) > 0)
		return ('c');
	else if (S_ISDIR(file_info->st_mode) > 0)
		return ('d');
	else if (S_ISFIFO(file_info->st_mode) > 0)
		return ('p');
	else if (S_ISLNK(file_info->st_mode) > 0)
		return ('l');
	else if (S_ISSOCK(file_info->st_mode) > 0)
		return ('s');
	else
		return ('-');
}

void	get_acl_and_xattr(t_files *file, char *fullname)
{
	acl_t		acl;
	acl_entry_t	acl_ent;
	ssize_t		attr_count;
	char		*tmp;

	acl = acl_get_link_np(fullname, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_ent) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	tmp = NULL;
	attr_count = listxattr(fullname, tmp, 0, XATTR_NOFOLLOW);
	file->perm[10] = ' ';
	if (attr_count > 0)
		file->perm[10] = '@';
	else if (acl != NULL)
		file->perm[10] = '+';
	file->perm[11] = ' ';
	file->perm[12] = '\0';
}

void	get_file_size(t_files *file, t_stat *file_info)
{
	if ((file->perm)[0] == 'b' || (file->perm)[0] == 'c')
	{
		file->major = (long)major(file_info->st_rdev);
		file->minor = (long)minor(file_info->st_rdev);
		file->special_files_exists = 1;
	}
	else
	{
		file->size = file_info->st_size;
		file->special_files_exists = 0;
	}
}
