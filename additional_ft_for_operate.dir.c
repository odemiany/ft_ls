/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_ft_for_operate.dir.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:11:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/11/01 04:30:56 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_dot(char *filename)
{
	if (filename[0] == '.')
	{
		if (ft_strlen(filename) == 1)
			return (1);
		else if (ft_strlen(filename) == 2 && filename[1] == '.')
			return (1);
	}
	return (0);
}

void	err_mgmt(char *str)
{
	ft_putstr("ls: ");
	perror(str);
}

int		count_flag(int not_dir_exists, size_t elem_count)
{
	if (not_dir_exists == 0 && elem_count == 1)
		return (0);
	else
		return (1);
}

void	write_fold_name(char *str)
{
	static int call_times = 0;

	if (call_times != 0)
		ft_putstr("\n");
	ft_putstr(str);
	ft_putendl(":");
	call_times++;
}

char	*make_next_name(char *fold_name, char *file_name)
{
	char	*tmp;
	char	*ret;

	ret = ft_strjoin(fold_name, "/");
	tmp = ret;
	ret = ft_strjoin(ret, file_name);
	free(tmp);
	return (ret);
}
