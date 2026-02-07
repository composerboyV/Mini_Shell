/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:12:00 by dukim             #+#    #+#             */
/*   Updated: 2024/12/24 19:12:04 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "../tokenizer/tokenizer.h"

static t_bool	is_redirection_type(char type)
{
	if (type == '>' || type == '<' || type == '+' || type == '-')
		return (true);
	return (false);
}

static int	handle_token_tocmd(t_list **cmdlst, t_command **command, \
								t_token *token, t_list **arg_list)
{
	static char	type;

	if (!cmdlst)
	{
		type = 0;
		return (0);
	}
	if (token->type == SYMBOL)
	{
		if (type)
			return (-1);
		type = *(token->content);
		if (type == '|')
		{
			append_cmd_inlist(cmdlst, *command, arg_list);
			*command = ft_calloc(sizeof(t_command), 1);
		}
		return (0);
	}
	if (is_redirection_type(type))
		connect_redirection(*command, token->content, type);
	else
		ft_lstadd_back(arg_list, ft_lstnew(ft_strdup(token->content)));
	type = 0;
	return (1);
}

void	token_tocmdunit(t_list *tokenlst, t_list **cmdlst)
{
	t_command	*command;
	t_list		*arg_list;
	int			res;

	command = ft_calloc(sizeof(t_command), 1);
	arg_list = NULL;
	while (tokenlst)
	{
		res = handle_token_tocmd(cmdlst, &command, \
								tokenlst->content, &arg_list);
		if (res == -1)
			break ;
		tokenlst = tokenlst->next;
	}
	if (res == 0 || res == -1)
	{
		ft_lstclear(cmdlst, free_command);
		ft_lstclear(&arg_list, free);
		free_command(command);
	}
	else
		append_cmd_inlist(cmdlst, command, &arg_list);
	handle_token_tocmd(NULL, NULL, NULL, NULL);
}
