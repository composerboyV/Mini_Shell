/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:36:23 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 17:37:39 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_bool	is_specital_tokench(char ch)
{
	if (ch == ' ' || ch == '|' || ch == '>' || ch == '<')
		return (true);
	return (false);
}

static void	word_tosymbol(char **line, t_word *word, char symbol)
{
	if (ft_strncmp(*line, ">>", 2) == 0)
	{
		symbol = '+';
		(*line)++;
	}
	if (ft_strncmp(*line, "<<", 2) == 0)
	{
		symbol = '-';
		(*line)++;
	}
	word->content[0] = symbol;
	word->content[1] = '\0';
	word->idx = 1;
}

static int	specitalch_handler(t_list **tokenlst, char **line, \
								t_word *word, t_envval *env_val)
{
	char	ch;

	ch = **line;
	if (is_quote_ch(ch))
	{
		quote_parser(line, word);
		if (!word->content)
			return (-1);
		return (0);
	}
	if (is_specital_tokench(ch))
	{
		append_token_inlist(tokenlst, word, WORD, env_val);
		if (ch != ' ')
		{
			word_tosymbol(line, word, ch);
			append_token_inlist(tokenlst, word, SYMBOL, env_val);
		}
		return (0);
	}
	return (1);
}

t_list	*tokenize(char *line, t_envval *env_val)
{
	t_list	*tokenlst;
	t_word	*word;
	int		res;

	tokenlst = NULL;
	word = malloc(sizeof(t_word) * 1);
	init_word(word);
	while (*line)
	{
		res = specitalch_handler(&tokenlst, &line, word, env_val);
		if (res == -1)
		{
			ft_lstclear(&tokenlst, free_token);
			break ;
		}
		if (res == 1)
			append_ch_inword(word, *line);
		line++;
	}
	append_token_inlist(&tokenlst, word, WORD, env_val);
	free(word->content);
	free(word);
	return (tokenlst);
}
