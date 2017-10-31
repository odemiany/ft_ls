/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_long_output2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 01:41:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/31 01:41:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_last_modified_time(t_files *file, t_stat *file_info)
{
	time_t	file_time;
	char	*readable_time;
	int		six_months;
	int		i;

	file_time = file_info->st_mtime;
	readable_time = ctime(&file_time);
	six_months = 6 * 30 * 24 * 60 * 60;
	i = -1;
	while (++i < 7)
		file->last_modified[i] = readable_time[i + 4];
	if (time(NULL) - file_time > six_months)
	{
		file->last_modified[7] = ' ';
		i = 7;
		while (++i < 12)
			file->last_modified[i] = readable_time[i + 12];
	}
	else
	{
		while (++i < 13)
			file->last_modified[i - 1] = readable_time[i + 3];
	}
	file->last_modified[12] = ' ';
	file->last_modified[13] = '\0';
}

void	count_total_blocks(t_files *file, char *fold_name)
{
	blkcnt_t	total_blocks;
	t_stat		file_info;
	char		*fullname;

	total_blocks = 0;
	while (file != NULL)
	{
		fullname = make_next_name(fold_name, file->file);
		lstat(fullname, &file_info);
		total_blocks += file_info.st_blocks;
		free(fullname);
		file = file->next;
	}
	ft_putstr("total ");
	ft_putnbr((int)total_blocks);
	ft_putstr("\n");
}

size_t	count_num(long long int n)
{
	size_t num;

	if (n == 0)
		return (1);
	num = 0;
	while (n != 0)
	{
		num++;
		n = n / 10;
	}
	return (num);
}

void	print_space(size_t num)
{
	while (num > 0)
	{
		write(1, " ", 1);
		num--;
	}
}

void	print_size(t_files *file, t_len *max_len)
{
	if (file->special_files_exists == 1)
	{
		ft_putnbr((int) file->major);
		ft_putstr(", ");
		print_space(max_len->size - count_num(file->major) -
							count_num(file->minor) - 2);
		ft_putnbr((int) file->minor);
	}
	else
	{
		print_space(max_len->size - count_num(file->size));
		ft_putnbr((int) file->size);
	}
	write(1, " ", 1);
}