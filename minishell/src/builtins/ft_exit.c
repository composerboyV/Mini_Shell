/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:48:18 by dukim             #+#    #+#             */
/*   Updated: 2024/11/29 21:48:19 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_bool	is_numeric(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	ft_exit(char **args, t_bool is_child)
{
	char	exit_code;

	if (!is_child)
		ft_putendl_fd("exit", 2);
	exit_code = 0;
	if (!args[1])
		return (exit_code);
	if (is_numeric(args[1]))
	{
		exit_code = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
	}
	else
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		exit_code = 2;
	}
	return (exit_code);
}
