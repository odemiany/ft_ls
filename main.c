/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 16:20:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 04:39:04 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	ft_ls(ac, av);
	return (0);
}

void	ft_ls(int av, char **ac)
{
	t_ls_struct		s_info;
	char			*fold_name;

	s_info.flags = "\0";
	fold_name = "\0";
	fold_name = ft_strjoin(fold_name, "\0");
	parse_params(av, ac, &s_info);
	check_flags(&s_info);
	apply_sorting(s_info.flags, s_info.unsorted, &(s_info.unsorted), fold_name);
	split_dir_and_not_dir(&s_info);
	operate_not_dir(&s_info);
	operate_dir(&s_info);
	free(fold_name);
}
