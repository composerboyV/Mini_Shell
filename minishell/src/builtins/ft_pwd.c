/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:35:35 by dukim             #+#    #+#             */
/*   Updated: 2025/01/05 20:35:36 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_envval *env_val)
{
	char	str[1024];

	(void)env_val;
	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
	return (0);
}
