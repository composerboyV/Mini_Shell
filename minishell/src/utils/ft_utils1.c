/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:48:57 by dukim             #+#    #+#             */
/*   Updated: 2024/12/13 19:48:59 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_bool	is_quote_ch(char ch)
{
	if (ch == '\'' || ch == '"')
		return (true);
	return (false);
}

char	**ft_lst_toarray(t_list *lst)
{
	char	**array;
	size_t	i;

	if (!lst)
		return (0);
	array = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		array[i++] = ft_strdup((const char *)lst->content);
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_strdivide(char *str, int c)
{
	char	**divide;
	size_t	i;
	size_t	len;

	divide = malloc(sizeof(char *) * 2);
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == c)
			break ;
		i++;
	}
	divide[0] = ft_substr(str, 0, i);
	if (i == len)
		divide[1] = NULL;
	else
		divide[1] = ft_substr(str, i + 1, len);
	return (divide);
}
