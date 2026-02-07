/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:20:25 by dukim             #+#    #+#             */
/*   Updated: 2025/01/08 02:20:28 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_stderr(const char *str1, const char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	perror(str);
	free(str);
}

void	print_exporterr_ch(char ch)
{
	ft_putstr_fd("export: '", 2);
	ft_putchar_fd(ch, 2);
	ft_putendl_fd("': not valid identifier", 2);
}

void	print_exporterr_str(char *str)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not valid identifier", 2);
}
