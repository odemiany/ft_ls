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
			free(list->file);
			free(list);
			list = tmp;
		}
	}
}

size_t	count_elem(t_files *list)
{
	size_t i;

	i = 0;
	while (list != NULL)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void 	add_to_list(char *str, t_files *file, t_files **file_ptr)
{
	if (!str || !file_ptr)
		return ;
	if (*file_ptr == NULL)
	{
		*file_ptr = (t_files *)malloc(sizeof(t_files));
		(*file_ptr)->next = NULL;
		(*file_ptr)->prev = NULL;
		(*file_ptr)->file = ft_strdup(str);
		return ;
	}
	while (file->next != NULL)
		file = file->next;
	file->next = (t_files *)malloc(sizeof(t_files));
	file->next->next = NULL;
	file->next->prev = file;
	file->next->file = ft_strdup(str);
}

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
