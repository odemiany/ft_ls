/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 15:17:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/19 15:17:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# define FLAG 1
# define NOT_FLAG -1
# define DELIMITER 2
# define ALLOWED_FLAGS "alrRt"
# define LEXICOGRAPHIC 0
# define REVERSE 1
# define BY_TIME 2

typedef struct		s_files
{
	char			*file;
	struct s_files	*prev;
	struct s_files	*next;
}					t_files;

typedef struct		s_ls_struct
{
	char			*flags;
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
void				add_to_files(char *str, t_ls_struct *s_info);
void				add_to_dir(char *str, t_ls_struct *s_info);
void				add_to_not_dir(char *str, t_ls_struct *s_info);
void				free_list(t_files *list);
void				ret_ptr_to_head(t_files *list, t_files **list_ptr);
t_files				*find_last_elem(t_files *list);
void				reverse_list(t_files *list, t_files **list_ptr);
void				sort_input_params(t_ls_struct *s_info);
#endif
