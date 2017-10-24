/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_folder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:13:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/24 19:13:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_simple_folder(t_files *file)
{
	if (!file)
		return ;
	while (file != NULL)
	{
		ft_putendl(file->file);
		file = file->next;
	}
}

void	print_extend_folder(t_files *file)
{
	if (!file)
		return ;
	while (file != NULL)
	{
		ft_putstr("*EXTEND* ");
		ft_putstr(file->file);
		ft_putendl(" *EXTEND*");
		file = file->next;
	}
}