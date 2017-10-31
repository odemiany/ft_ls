/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_long_output3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 08:11:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/31 08:11:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_softlink(char *fullname, t_files *file)
{
	char	softlink[1024];
	ssize_t	link_len;

	if (file->perm[0] == 'l')
	{
		link_len = readlink(fullname, softlink, 1023);
		if (link_len != -1)
		{
			softlink[link_len] = '\0';
			file->linkpath = ft_strdup(softlink);
		}
		else
			file->linkpath = ft_strdup("");
	}
}

void	print_softlink(t_files *file)
{
	ft_putstr(file->file);
	ft_putstr(" -> ");
	ft_putendl(file->linkpath);
	free(file->linkpath);
}
