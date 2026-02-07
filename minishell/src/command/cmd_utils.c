/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:23:36 by dukim             #+#    #+#             */
/*   Updated: 2024/12/24 22:23:37 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "command.h"

static char	*get_cmd_relativepath(char *cmd)
{
	char	pwd[1024];
	char	*path;
	char	*temp;

	getcwd(pwd, sizeof(char) * 1024);
	temp = ft_strjoin(pwd, "/");
	path = ft_strjoin(temp, cmd);
	free(temp);
	return (path);
}

char	*get_cmd_abspath(char *cmd, t_list *envlst)
{
	char	*cmd_path;
	int		i;
	char	**path_list;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	if (cmd[0] == '.')
		return (get_cmd_relativepath(cmd));
	path_list = ft_split(ft_getenv("PATH", envlst), ':');
	if (!path_list)
		return (NULL);
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (path_list[++i])
	{
		cmd_path = ft_strjoin(path_list[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
	}
	free(cmd);
	if (!path_list[i])
		cmd_path = NULL;
	ft_freesplit(path_list);
	return (cmd_path);
}

void	append_cmd_inlist(t_list **lst, t_command *command, t_list **arg_list)
{
	command->args = ft_lst_toarray(*arg_list);
	ft_lstclear(arg_list, free);
	ft_lstadd_back(lst, ft_lstnew(command));
}

void	free_command(void *ptr)
{
	t_command		*command;
	t_redirection	*redi;

	if (!ptr)
		return ;
	command = (t_command *)ptr;
	ft_freesplit(command->args);
	redi = command->redi;
	while (redi)
	{
		ptr = redi->next;
		free(redi->file);
		free(redi);
		redi = ptr;
	}
	free(command);
}
