/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:12:55 by junkwak           #+#    #+#             */
/*   Updated: 2025/01/07 17:35:59 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_bool	is_valid_exportname(char *name)
{
	int	p;

	if (ft_isalpha(name[0]) == 0 && name[0] != '_')
	{
		print_exporterr_ch(name[0]);
		return (false);
	}
	p = 0;
	while (name[p])
	{
		if ((ft_isalnum(name[p]) == 0 && name[p] != '_') || name[p] == '=')
		{
			if (((name[p] == '+' && name[p + 1] == '=')) \
				|| (name[p] == '=' && name[p - 1] != '\0'))
				return (true);
			print_exporterr_str(name);
			return (false);
		}
		p++;
	}
	return (true);
}

static t_env	*create_env_node(char *envvalue)
{
	t_env	*node;
	char	**temp;

	node = (t_env *)malloc(sizeof(t_env));
	temp = ft_strdivide(envvalue, '=');
	node->key = temp[0];
	node->value = temp[1];
	free(temp);
	return (node);
}

static t_bool	check_overlapname(char *key, char *value, t_list *lst)
{
	t_env	*env;

	if (key == NULL)
		return (0);
	while (lst)
	{
		env = lst->content;
		if (ft_strncmp(key, env->key, ft_strlen(key) + 1) == 0)
		{
			if (env->value)
				free(env->value);
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = ft_strdup("");
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}

static int	append_envvalue(char **cmds, t_list *env_list, t_bool *is_changed)
{
	t_env	*node;
	int		i;
	int		result;

	result = 0;
	i = 0;
	while (cmds[++i])
	{
		if (!is_valid_exportname(cmds[i]))
		{
			result = 1;
			continue ;
		}
		*is_changed = true;
		node = create_env_node(cmds[i]);
		if (check_overlapname(node->key, node->value, env_list))
			free_env(node);
		else
			ft_lstadd_back(&env_list, ft_lstnew(node));
	}
	return (result);
}

int	ft_export(char **args, t_envval *env_val)
{
	t_list	*ptr;
	int		result;

	result = 0;
	if (args[1] == NULL)
	{
		ptr = env_val->lst;
		while (ptr)
		{
			export_print(ptr);
			ptr = ptr->next;
		}
		return (0);
	}
	else
		result = append_envvalue(args, env_val->lst, &(env_val->is_changed));
	return (result);
}
