/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:49:18 by dukim             #+#    #+#             */
/*   Updated: 2025/01/09 04:49:51 by dukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	*heredoc_handler(const char *delimiter)
{
	int		fd;
	char	*line;
	char	*tmpfile;

	tmpfile = ft_strjoin(".heredoc_", delimiter);
	fd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (fd != -1)
	{
		set_sigall(true);
		line = readline("> ");
		if ((!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (tmpfile);
}
