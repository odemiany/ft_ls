/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:14:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/20 18:14:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_flags(t_ls_struct *s_info)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s_info->flags))
	{
		if (ft_strchr(ALLOWED_FLAGS, (s_info->flags)[i]) == NULL)
		{
			ft_putstr("ls: illegal option -- ");
			ft_putchar((s_info->flags)[i]);
			ft_putstr("\n");
			print_usage();
		}
		i++;
	}
}
void	print_usage(void)
{
	char *flags;

	flags = ALLOWED_FLAGS;
	ft_putstr("usage: ls [-");
	ft_putstr(flags);
	ft_putstr("] [file ...]\n");
	exit(1);
}