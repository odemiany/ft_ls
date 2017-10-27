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

//	tmp = s_info->unsorted;
//	while (tmp != NULL)
//	{
//		printf("%s\n", tmp->file);
//		tmp = tmp->next;
//	}
	printf("NOT_DIR:\n");
	tmp = s_info->not_dir;
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
	printf("DIR:\n");
	tmp = s_info->dir;
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
	sort_list(s_info.unsorted, LEXICOGRAPHIC, &(s_info.unsorted));
	split_dir_and_not_dir(&s_info);
	operate_not_dir(&s_info);
	operate_dir(&s_info);
	while (42);
	//self_check(&s_info);
}
