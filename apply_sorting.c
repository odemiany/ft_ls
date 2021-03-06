/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 13:53:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 05:37:07 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	apply_sorting(char *flags, t_files *file, t_files **file_ptr,
															char *fold_name)
{
	if (ft_strchr(flags, 'f') != NULL)
		return ;
	if (ft_strchr(flags, 't') != NULL)
	{
		get_mtime(file, fold_name);
		sort_list(file, BY_TIME, file_ptr);
	}
	else
		sort_list(file, LEXICOGRAPHIC, file_ptr);
	if (ft_strchr(flags, 'r') != NULL)
		sort_list(file, REVERSE, file_ptr);
}

void	sort_list(t_files *list, int type, t_files **list_ptr)
{
	t_files *start;
	t_files *finish;
	t_files *min;

	if (list == NULL || list_ptr == NULL || type < 0 || type > 2)
		return ;
	start = list;
	finish = find_last_elem(list);
	if (type == REVERSE)
	{
		reverse_list(start, list_ptr);
		return ;
	}
	while (start != finish)
	{
		if (type == LEXICOGRAPHIC)
			min = lex_min(start, finish);
		else
			min = time_min(start, finish);
		start = (start == min) ? start->next : start;
		finish = (finish == min) ? finish->prev : finish;
		move_to_end(min, list);
	}
	move_to_end(start, list);
	ret_ptr_to_head(list, list_ptr);
}

t_files	*lex_min(t_files *start, t_files *finish)
{
	t_files *min;

	if (start == NULL || finish == NULL)
		return (NULL);
	min = start;
	while (start != finish)
	{
		if (ft_strcmp(min->file, start->file) > 0)
			min = start;
		start = start->next;
	}
	if (ft_strcmp(min->file, start->file) > 0)
		min = start;
	return (min);
}

t_files	*time_min(t_files *start, t_files *finish)
{
	t_files		*min;

	if (start == NULL || finish == NULL)
		return (NULL);
	min = start;
	while (start != finish)
	{
		if ((start->mtime > min->mtime) ||
		((start->mtime == min->mtime) && (start->n_mtime > min->n_mtime)) ||
		((start->mtime == min->mtime) && (start->n_mtime == min->n_mtime) &&
		(ft_strcmp(min->file, start->file) > 0)))
			min = start;
		start = start->next;
	}
	if ((finish->mtime > min->mtime) ||
		((finish->mtime == min->mtime) && (finish->n_mtime > min->n_mtime)) ||
		((finish->mtime == min->mtime) && (finish->n_mtime == min->n_mtime) &&
		(ft_strcmp(min->file, finish->file) > 0)))
		min = finish;
	return (min);
}

void	move_to_end(t_files *min, t_files *unsorted)
{
	if (unsorted != NULL && min != NULL)
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
}
