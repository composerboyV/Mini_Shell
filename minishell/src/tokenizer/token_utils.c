/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:45:58 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 21:46:00 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_bool	is_dollarsep(char ch)
{
	if (ch == '\0')
		return (true);
	if (ch == ' ' || ch == '\'' || ch == '"' || ch == '$')
		return (true);
	return (false);
}

static	size_t	get_dollarvalue(t_word *word, char *pre, t_envval *env_val)
{
	char	*dollar;
	char	*envvalue;
	size_t	i;

	if (*pre == '?')
	{
		envvalue = ft_itoa(env_val->exit_code);
		append_str_inword(word, envvalue);
		free(envvalue);
		return (1);
	}
	dollar = ft_calloc(sizeof(char), ft_strlen(pre) + 1);
	i = 0;
	while (!is_dollarsep(*pre))
		dollar[i++] = *pre++;
	if (i == 0)
		return (1);
	envvalue = ft_getenv(dollar, env_val->lst);
	if (envvalue)
		append_str_inword(word, envvalue);
	free(dollar);
	return (i);
}

static void	convert_wordcotent(t_word *word, t_envval *envval)
{
	char	*pre;
	char	quote;
	size_t	i;

	pre = word->content;
	init_word(word);
	quote = 0;
	i = -1;
	while (pre[++i])
	{
		if (is_quote_ch(pre[i]))
		{
			if (quote == 0)
				quote = pre[i];
			else if (quote == pre[i])
				quote = 0;
			else
				append_ch_inword(word, pre[i]);
		}
		else if (pre[i] == '$' && !is_dollarsep(pre[i + 1]) && quote != '\'')
			i += get_dollarvalue(word, pre + i + 1, envval);
		else
			append_ch_inword(word, pre[i]);
	}
	free(pre);
}

void	append_token_inlist(t_list **tokenlst, t_word *word, \
							t_token_type type, t_envval *env_val)
{
	t_token	*token;

	if (word->idx == 0)
		return ;
	convert_wordcotent(word, env_val);
	if (word->content[0] == '\0')
		return ;
	token = malloc(sizeof(t_word) * 1);
	token->content = word->content;
	token->type = type;
	ft_lstadd_back(tokenlst, ft_lstnew(token));
	init_word(word);
}

void	free_token(void *ptr)
{	
	t_token	*token;

	token = (t_token *)ptr;
	free(token->content);
	free(token);
}
