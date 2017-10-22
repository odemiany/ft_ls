/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 15:39:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/22 15:39:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ret_ptr_to_head(t_files *list, t_files **list_ptr)
{
	if (list != NULL && list_ptr != NULL)
	{
		while (list->prev != NULL)
			list = list->prev;
		*list_ptr = list;
	}
}

t_files	*find_last_elem(t_files *list)
{
	if (list != NULL)
	{
		while (list->next != NULL)
			list = list->next;
	}
	return (list);
}

void	free_list(t_files *list)
{
	t_files *tmp;

	if (list != NULL)
	{
		while (list != NULL)
		{
			tmp = list->next;
			free(list);
			list = tmp;
		}
	}
}