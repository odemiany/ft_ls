/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_folder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:13:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/24 19:13:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	char *fullname;

	if (!file)
		return ;
	while (file != NULL)
	{
		fullname = make_next_name(fold_name, file->file);
		get_file_type_and_perm(file, fullname);
		get_acl_and_xattr(file, fold_name);
		ft_putstr(file->perm);
		ft_putstr(file->file);
		ft_putendl(" *EXTEND*");
		file = file->next;
		free(fullname);
	}
}

void	get_acl_and_xattr(t_files *file, char *fullname)
{
	acl_t		acl;
	acl_entry_t	acl_ent;
	ssize_t		attr_count;

	acl = acl_get_link_np(fullname, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_ent) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	attr_count = listxattr(fullname, NULL, 0, XATTR_NOFOLLOW);
	attr_count = (attr_count < 0) ? 0 : attr_count;
	if (attr_count > 0)
		file->perm[10] = '@';
	else if (acl != NULL)
		file->perm[10] = '+';
	else
		file->perm[10] = ' ';
	file->perm[11] = '\0';
}

void	get_file_type_and_perm(t_files *file, char *fullname)
{
	t_stat	file_info;

	lstat(fullname, &file_info);
	file->perm[0] = get_file_type(&file_info);
	(file_info.st_mode & S_IRUSR) ? file->perm[1] = 'r' : '-';
	(file_info.st_mode & S_IWUSR) ? file->perm[2] = 'w' : '-';
	(file_info.st_mode & S_IXUSR) ? file->perm[3] = 'x' : '-';
	(file_info.st_mode & S_IRGRP) ? file->perm[4] = 'r' : '-';
	(file_info.st_mode & S_IWGRP) ? file->perm[5] = 'w' : '-';
	(file_info.st_mode & S_IXGRP) ? file->perm[6] = 'x' : '-';
	(file_info.st_mode & S_IROTH) ? file->perm[7] = 'r' : '-';
	(file_info.st_mode & S_IWOTH) ? file->perm[8] = 'w' : '-';
	(file_info.st_mode & S_IXOTH) ? file->perm[9] = 'x' : '-';
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