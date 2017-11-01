/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 15:17:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 05:37:31 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# define FLAG 1
# define NOT_FLAG -1
# define DELIMITER 2
# define ALLOWED_FLAGS "adflrRt"
# define LEXICOGRAPHIC 0
# define REVERSE 1
# define BY_TIME 2

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct		s_len
{
	size_t			link;
	size_t			uid;
	size_t			gid;
	size_t			size;
}					t_len;

typedef struct		s_files
{
	struct s_files	*prev;
	char			*file;
	time_t			n_mtime;
	time_t			mtime;
	char			perm[13];
	nlink_t			st_nlink;
	char			*uid;
	char			*gid;
	off_t			size;
	long			major;
	long			minor;
	int				special_files_exists;
	char			last_modified[14];
	char			*linkpath;
	struct s_files	*next;
}					t_files;

typedef struct		s_ls_struct
{
	char			*flags;
	int				not_dir_exists;
	int				n_flag;
	t_files			*unsorted;
	t_files			*dir;
	t_files			*not_dir;
}					t_ls_struct;

void				ft_ls(int av, char **ac);
void				parse_params(int av, char **ac, t_ls_struct *s_info);
int					check_flag(char *str);
void				add_to_flags(char *str, t_ls_struct *s_info);
void				add_to_files(char *str, t_ls_struct *s_info);
void				check_flags(t_ls_struct *s_info);
void				print_usage(void);
void				sort_list(t_files *list, int type, t_files **list_ptr);
t_files				*lex_min(t_files *start, t_files *finish);
t_files				*time_min(t_files *start, t_files *finish);
void				move_to_end(t_files *min, t_files *unsorted);
void				split_dir_and_not_dir(t_ls_struct *s_info);
int					is_dir(char *filename);
void				add_to_dir(char *str, t_ls_struct *s_info);
void				add_to_not_dir(char *str, t_ls_struct *s_info);
void				free_list(t_files *list);
void				ret_ptr_to_head(t_files *list, t_files **list_ptr);
t_files				*find_last_elem(t_files *list);
void				reverse_list(t_files *list, t_files **list_ptr);
void				sort_input_params(t_ls_struct *s_info);
void				operate_dir(t_ls_struct *s_info);
void				operate_not_dir(t_ls_struct *s_info);
void				get_extend_data(t_files *list);
void				print_folder(t_files *file, t_ls_struct *s_info,
															char *fold_name);
void				print_extend_data(t_files *list);
size_t				count_elem(t_files *list);
int					count_flag(int file_exists, size_t elem_count);
void				write_fold_name(char *str);
void				apply_sorting(char *flags, t_files *file,
										t_files **file_ptr, char *fold_name);
void				read_folder(char *folder, t_files **file, char *flags);
void				print_simple_folder(t_files *file);
void				print_extend_folder(t_files *file, char *fold_name);
void				add_to_list(char *str, t_files *file, t_files **file_ptr);
void				err_mgmt(char *str);
void				recursion(char *str, t_ls_struct *s_info);
char				*make_next_name(char *fold_name, char *file_name);
void				get_mtime(t_files *list, char *fold_name);
int					is_dot(char *filename);
void				get_acl_and_xattr(t_files *file, char *fold_name);
void				get_file_type_and_perm(t_files *file, t_stat *file_info);
char				get_file_type(t_stat *file_info);
void				check_for_soft_link(char *filename, t_ls_struct *s_info);
void				permissions_part2(t_files *file, t_stat *file_info);
void				get_file_size(t_files *file, t_stat *file_info);
void				get_last_modified_time(t_files *file, t_stat *file_info);
void				count_total_blocks(t_files *file, char *fold_name);
void				print_data(t_files *file);
void				count_max_len(t_files *file, t_len *max_len);
size_t				count_num(long long int n);
void				print_space(size_t num);
void				print_size(t_files *file, t_len *max_len);
void				print_softlink(t_files *file);
void				check_softlink(char *fullname, t_files *file);
void				get_extend_stuff(t_files *file);
#endif
