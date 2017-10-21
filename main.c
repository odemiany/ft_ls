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
	t_files	*tmp;
	t_files	*tmp2;

	printf("flags:\n%s\nfiles:\n", s_info->flags);
	tmp = s_info->unsorted;
	tmp2 = NULL;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->file);
		tmp2 = tmp;
		tmp = tmp->next;
	}
	while(tmp2 != NULL)
	{
		printf("%s\n", tmp2->file);
		tmp2 = tmp2->prev;
	}
	//sleep(100);
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
	check_flags(&s_info);
	sort_input_files(&s_info);
	self_check(&s_info);
}