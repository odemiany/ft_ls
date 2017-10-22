/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 19:05:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/22 19:05:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	operate_not_dir(t_ls_struct *s_info)
{
	t_files	*list;
	t_files	*file;
	size_t	elem_count;

	list = s_info->dir;
	if (list == NULL)
		return;
	file = NULL;
	elem_count = count_elem(list);
	while (list != NULL)
	{
		check_count(elem_count, list->file);
		read_folder(list->file, &file, s_info->flags);
		if (ft_strchr(s_info->flags, 'i') != NULL)
			sort_list(file, BY_TIME, &file);
		else
			sort_list(file, LEXICOGRAPHIC, &file);
		if (ft_strchr(s_info->flags, 'r') != NULL)
			sort_list(file, REVERSE, &file);
		if (ft_strchr(s_info->flags, 'l') == NULL)
			ft_putendl(list->file);
		else
			//print_extend_folder(file);
		list = list->next;
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

void	check_count(size_t i, char *str)
{
	if (i > 1)
	{
		ft_putstr(str);
		ft_putendl(":");
	}
}

void	read_folder(char *folder, t_list **file, char *flags)
{
	DIR *dir;

	dir = opendir(folder);
	if (dir == NULL)
		return NULL;
}