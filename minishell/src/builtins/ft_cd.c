/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:43:30 by dukim             #+#    #+#             */
/*   Updated: 2025/01/06 21:10:19 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	chdir_suc(char *pwd, char *old_pwd, t_list *env_list)
{
	if (getcwd(pwd, sizeof(char) * 1024) == NULL)
		return ;
	replace_envvalue("OLDPWD", old_pwd, env_list);
	replace_envvalue("PWD", pwd, env_list);
}

static char	*find_grammer(char **args, t_list *env_list)
{
	char	*way;

	way = args[1];
	if (ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0)
		way = ft_getenv("HOME", env_list);
	return (way);
}

int	ft_cd(char **args, t_list *env_list)
{
	char	*phys_path;
	char	*old_pwd;
	char	pwd[1024];

	if (args[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (args[2] != NULL)
	{
		ft_putendl_fd("cd: too many argument", 2);
		return (1);
	}
	phys_path = find_grammer(args, env_list);
	if (chdir(phys_path) == -1)
	{
		phys_path = ft_strjoin("cd: ", strerror(errno));
		ft_putendl_fd(phys_path, 2);
		free(phys_path);
		return (1);
	}
	old_pwd = ft_getenv("PWD", env_list);
	chdir_suc(pwd, old_pwd, env_list);
	return (0);
}
