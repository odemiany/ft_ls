/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_not_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 18:45:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/22 18:45:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	operate_not_dir(t_ls_struct *s_info)
{
	t_files	*list;

	list = s_info->not_dir;
	if (list == NULL)
		return ;
	while (list != NULL)
	{
		if (ft_strchr(s_info->flags, 'l') == NULL)
			ft_putendl(list->file);
		else
		{
			//get_extend_data(list);
			//print_extend_data(list);
			ft_putstr("extend:");
			ft_putendl(list->file);
		}
		list = list->next;
	}
	free_list(s_info->not_dir);
}

