/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:32:05 by dukim             #+#    #+#             */
/*   Updated: 2024/12/22 19:45:03 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parser_handler(char *line, t_envval *env_val)
{
	t_list	*tokenlst;
	t_list	*cmdlst;
	size_t	cmdlst_len;
	int		res;

	if (!line || line[0] == '\0')
		return (1);
	tokenlst = tokenize(line, env_val);
	if (!tokenlst)
		return (1);
	cmdlst = NULL;
	token_tocmdunit(tokenlst, &cmdlst);
	ft_lstclear(&tokenlst, free_token);
	if (!cmdlst)
		return (1);
	cmdlst_len = ft_lstsize(cmdlst);
	excute_handler(cmdlst, cmdlst_len, &res, env_val);
	ft_lstclear(&cmdlst, free_command);
	add_history(line);
	return (res);
}
