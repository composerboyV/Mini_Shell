/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:12:06 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 21:39:53 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static int	singlecmd_handler(t_list *cmdlst, size_t cmdlst_len, \
								t_envval *envval)
{
	t_command	*cmd;

	cmd = (t_command *)cmdlst->content;
	if (!cmd->args)
		return (0);
	if (cmdlst_len == 1 && ft_strncmp("exit", cmd->args[0], 5) == 0)
	{
		envval->exit_code = ft_exit(cmd->args, false);
		return (EXIT_CODE);
	}
	if (cmdlst_len == 1 && is_builtin_cmd(cmd->args[0]))
	{
		envval->exit_code = builtin_handler(cmd, envval);
		return (1);
	}
	return (0);
}

static int	execute_command(t_command *cmd, t_envval *env_val)
{
	int		fd[2];
	char	*cmd_path;

	if (!redirect_io(cmd->redi, fd))
		return (1);
	if (!cmd->args || cmd->args[0][0] == '\0')
		return (0);
	if (is_builtin_cmd(cmd->args[0]))
		return (builtin_handler(cmd, env_val));
	convert_lst_toenvp(env_val);
	cmd_path = get_cmd_abspath(cmd->args[0], env_val->lst);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	execve(cmd_path, cmd->args, env_val->envp);
	unredirect_io(cmd->redi, fd);
	free(cmd_path);
	return (1);
}

static void	execute_childpipe(t_list *cmdlst, int *fd, \
								int input_fd, t_envval *envval)
{
	dup2(input_fd, STDIN_FILENO);
	if (cmdlst->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	envval->exit_code = execute_command(cmdlst->content, envval);
}

static int	execute_multicmd(t_list *cmdlst, t_envval *envval, \
								pid_t *pids, int *fds)
{
	size_t	i;
	int		fd[2];
	int		input_fd;

	set_terminal(true);
	i = -1;
	input_fd = 0;
	while (cmdlst)
	{
		pipe(fd);
		fds[++i] = fd[0];
		set_sigall(false);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			execute_childpipe(cmdlst, fd, input_fd, envval);
			return (EXIT_CODE);
		}
		set_sigall(true);
		close(fd[1]);
		input_fd = fd[0];
		cmdlst = cmdlst->next;
	}
	return (1);
}

void	excute_handler(t_list *cmdlst, size_t cmdlst_len, \
					int *res, t_envval *env_val)
{
	pid_t	*pids;
	int		*fds;
	size_t	i;
	int		status;

	*res = singlecmd_handler(cmdlst, cmdlst_len, env_val);
	if (*res)
		return ;
	pids = malloc(sizeof(pid_t) * cmdlst_len);
	fds = malloc(sizeof(int) * cmdlst_len);
	*res = execute_multicmd(cmdlst, env_val, pids, fds);
	if (*res > 0)
	{
		i = -1;
		while (++i < cmdlst_len)
		{
			waitpid(pids[i], &status, 0);
			close(fds[i]);
			env_val->exit_code = get_child_exitcode(status);
		}
		print_sigmsg(env_val->exit_code);
	}
	free(fds);
	free(pids);
}
