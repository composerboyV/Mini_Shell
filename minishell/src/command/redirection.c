/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:27:42 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 13:27:43 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static t_bool	redirect(char *file_path, char type)
{
	int	fd;

	if (type == '>')
		fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == '+')
		fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
	{
		fd = open(file_path, O_RDONLY);
		if (type == '-')
			unlink(file_path);
	}
	if (fd == -1)
	{
		print_stderr("bash: ", file_path);
		return (false);
	}
	if (type == '>' || type == '+')
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (true);
}

void	connect_redirection(t_command *command, char *file, char type)
{
	t_redirection	*ptr;
	t_redirection	*redi;

	redi = malloc(sizeof(t_redirection) * 1);
	if (type == '-')
		redi->file = heredoc_handler(file);
	else
		redi->file = ft_strdup(file);
	redi->type = type;
	redi->next = NULL;
	if (command->redi == NULL)
		command->redi = redi;
	else
	{
		ptr = command->redi;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = redi;
	}
}

t_bool	redirect_io(t_redirection *redi, int fd[2])
{
	if (!redi)
		return (true);
	fd[0] = dup(0);
	fd[1] = dup(1);
	while (redi)
	{
		if (!redirect(redi->file, redi->type))
		{
			unredirect_io(redi, fd);
			return (false);
		}
		redi = redi->next;
	}
	return (true);
}

void	unredirect_io(t_redirection *redi, int fd[2])
{
	if (!redi)
		return ;
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}
