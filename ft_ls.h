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
# define FLAG 1
# define NOT_FLAG -1
# define DELIMITER 2
# define ALLOWED_FLAGS "ailRt"

typedef struct		s_files
{
	char			*file;
	struct s_files	*next;
}					t_files;

typedef struct		s_ls_struct
{
	char			*flags;
	t_files			*unsorted;
}					t_ls_struct;

void				ft_ls(int av, char **ac);
void				parse_params(int av, char **ac, t_ls_struct *s_info);
int					check_flag(char *str);
void				add_to_flags(char *str, t_ls_struct *s_info);
void				add_to_files(char *str, t_ls_struct *s_info);
void				check_flags(t_ls_struct *s_info);
void				print_usage(void);
#endif
