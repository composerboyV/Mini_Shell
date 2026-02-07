/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:34:51 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 17:36:27 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_unset(t_list *head, t_env *env)
{
	free(head);
	free(env->key);
	free(env->value);
	free(env);
}

static void	us_handler(t_list *head, t_list *bf_head, \
						t_envval *env_val, t_env *env)
{
	env_val->is_changed = true;
	if (head->next && !bf_head)
	{
		env_val->lst = env_val->lst->next;
		bf_head = head->next;
		free_unset(head, env);
		return ;
	}
	if (head->next)
		bf_head->next = head->next;
	else
	{
		bf_head->next = NULL;
	}
	free_unset(head, env);
}

int	ft_unset(char **args, t_envval *env_val)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '=') != 0)
			return (0);
		current = env_val->lst;
		prev = NULL;
		while (current)
		{
			env = current->content;
			if (ft_strncmp(env->key, args[i], ft_strlen(env->key) + 1) == 0)
			{
				us_handler(current, prev, env_val, env);
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
	return (0);
}
