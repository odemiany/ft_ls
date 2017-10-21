/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 13:53:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/21 13:53:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_input_files(t_ls_struct *s_info)
{
	t_files *start;
	t_files *finish;
	t_files *min;

	start = s_info->unsorted;
	while (start->next != NULL)
		start = start->next;
	finish = start;
	start = s_info->unsorted;
	while (start != finish)
	{
		min = find_min_between(start, finish);
		if (start == min)
			start = start->next;
		if (finish == min)
			finish = finish->prev;
		move_to_end(min, s_info->unsorted);
	}
	move_to_end(start, s_info->unsorted);
	while (s_info->unsorted->prev != NULL)
		s_info->unsorted = s_info->unsorted->prev;
}

t_files	*find_min_between(t_files *start, t_files *finish)
{
	t_files *min;

	min = start;
	while (start != finish)
	{
		if (strcmp(min->file, start->file) > 0)
			min = start;
		start = start->next;
	}
	if (strcmp(min->file, start->file) > 0)
		min = start;
	return (min);
}

void	move_to_end(t_files *min, t_files *unsorted)
{
	while (unsorted->next != NULL)
		unsorted = unsorted->next;
	if (min->prev != NULL && min->next != NULL)
		min->prev->next = min->next;
	if (min->next != NULL)
		min->next->prev = min->prev;
	if (min != unsorted)
	{
		unsorted->next = min;
		min->next = NULL;
		min->prev = unsorted;
	}
}