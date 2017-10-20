/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 16:20:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/19 16:20:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

void	self_check(t_ls_struct *s_info)
{
	printf("%s\n", s_info->flags);
	sleep(100);
}

int main(int ac, char **av)
{
	ft_ls(ac, av);
	return 0;
}

void 	ft_ls(int av, char **ac)
{
	t_ls_struct		s_info;

	s_info.flags = "\0";
	parse_params(av, ac, &s_info);
	self_check(&s_info);
}