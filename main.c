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

int main(int ac, char **av)
{
	ft_ls(ac, av);
	return 0;
}

void 	ft_ls(int av, char **ac)
{
	t_ls_struct		s_info;

	parse_params(av, ac, &s_info);
}