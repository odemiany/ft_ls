/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 04:34:36 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 05:08:32 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverse_list(t_files *list, t_files **list_ptr)
{
	t_files *list_cp;
	t_files *tmp;

	if (list == NULL || list_ptr == NULL)
		return ;
	while (list->prev != NULL)
		list = list->prev;
	list_cp = list;
	while (list_cp != NULL)
	{
		tmp = list_cp->prev;
		list_cp->prev = list_cp->next;
		list_cp->next = tmp;
		list_cp = list_cp->prev;
	}
	ret_ptr_to_head(list, list_ptr);
}
