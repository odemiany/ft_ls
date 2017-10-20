/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odemiany <odemiany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 09:18:00 by odemiany          #+#    #+#             */
/*   Updated: 2017/10/20 09:18:00 by odemiany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_params(int ac, char **av, t_ls_struct *s_info)
{
	int	i;

	if (ac == 1)
	{
		/*add "." to files*/
		return ;
	}
	i = 1;
	while (i < ac && check_flag(av[i]) == FLAG)
	{
		add_to_flags(av[i], s_info);
		i++;
	}
	if (i < ac && check_flag(av[i]) == DELIMITER)
		i++;
	while (i < ac)
	{
		//add_to_files(av[i]);
		i++;
	}
}

int		check_flag(char *str)
{
	if (ft_strlen(str) == 2 && *str == '-' && *(str + 1) == '-')
		return (DELIMITER);
	else if (ft_strlen(str) > 1 && *str == '-')
		return (FLAG);
	else
		return (NOT_FLAG);
}

void	add_to_flags(char *str, t_ls_struct *s_info)
{
	char *ptr_cp;

	ptr_cp = s_info->flags;
	s_info->flags = ft_strjoin(s_info->flags, (str + 1));
	if (*ptr_cp)
		free(ptr_cp);
}