/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:57:02 by dukim             #+#    #+#             */
/*   Updated: 2025/01/06 21:04:35 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../command/command.h"

t_bool	is_builtin_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0 || \
		ft_strncmp(cmd, "exit", 5) == 0 || \
		ft_strncmp(cmd, "env", 4) == 0 || \
		ft_strncmp(cmd, "export", 7) == 0 || \
		ft_strncmp(cmd, "unset", 5) == 0 || \
		ft_strncmp(cmd, "pwd", 3) == 0 || \
		ft_strncmp(cmd, "echo", 4) == 0)
		return (true);
	return (false);
}

int	builtin_handler(void *ptr, t_envval *env_val)
{
	t_command	*cmd;
	int			fd[2];
	int			res;

	cmd = (t_command *)ptr;
	res = 1;
	if (!redirect_io(cmd->redi, fd))
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		res = ft_cd(cmd->args, env_val->lst);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		res = ft_exit(cmd->args, true);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		res = ft_env(cmd->args, env_val->lst);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		res = ft_export(cmd->args, env_val);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		res = ft_unset(cmd->args, env_val);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		res = ft_pwd(env_val);
	else if (ft_strncmp(*cmd->args, "echo", 4) == 0)
		res = ft_echo(cmd->args);
	unredirect_io(cmd->redi, fd);
	return (res);
}
