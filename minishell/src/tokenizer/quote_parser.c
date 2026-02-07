/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:45:38 by dukim             #+#    #+#             */
/*   Updated: 2024/12/06 19:45:39 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_word	*get_quoteword(char **line, char quote)
{
	t_word	*word;
	t_bool	flag;

	word = malloc(sizeof(t_word) * 1);
	init_word(word);
	flag = 0;
	while (**line)
	{
		append_ch_inword(word, **line);
		if (flag && quote == **line)
			return (word);
		(*line)++;
		flag = true;
	}
	free(word->content);
	free(word);
	return (NULL);
}

void	quote_parser(char **line, t_word *word)
{
	t_word	*qutoeword;
	char	*temp;

	qutoeword = get_quoteword(line, **line);
	if (!qutoeword)
	{
		free(word->content);
		word->content = NULL;
		word->idx = 0;
		return ;
	}
	temp = word->content;
	word->content = ft_strjoin(word->content, qutoeword->content);
	word->max_len = ft_strlen(word->content);
	word->idx = word->max_len;
	free(temp);
	free(qutoeword->content);
	free(qutoeword);
}
