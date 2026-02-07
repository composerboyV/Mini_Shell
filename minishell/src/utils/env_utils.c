/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 21:19:33 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(const char *env, t_list *env_list)
{
	size_t	len;

	len = ft_strlen(env);
	while (env_list)
	{
		if (ft_strncmp(((t_env *)env_list->content)->key, env, len +1) == 0)
			return (((t_env *)env_list->content)->value);
		env_list = env_list->next;
	}	
	return (NULL);
}

void	replace_envvalue(const char *env, char *replace, t_list *env_list)
{
	size_t	len;

	len = ft_strlen(env);
	while (env_list)
	{
		if (ft_strncmp(((t_env *)env_list->content)->key, env, len +1) == 0)
		{
			free(((t_env *)env_list->content)->value);
			((t_env *)env_list->content)->value = ft_strdup(replace);
			return ;
		}
		env_list = env_list->next;
	}	
}

t_list	*init_env_list(char **envp)
{
	t_list	*env_list;
	t_env	*node;
	int		i;
	char	**temp;

	env_list = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = (t_env *)malloc(sizeof(t_env));
		temp = ft_strdivide(envp[i], '=');
		node->key = temp[0];
		node->value = temp[1];
		i++;
		ft_lstadd_back(&env_list, ft_lstnew(node));
		free(temp);
	}
	return (env_list);
}

void	free_env(void *ptr)
{
	t_env	*env;

	env = (t_env *)ptr;
	free(env->key);
	free(env->value);
	free(env);
}

void	export_print(t_list *ptr)
{
	t_env	*env;

	env = ptr->content;
	if (!(ft_strlen(env->key) == 1 && ft_strncmp(env->key, "_", 1) == 0))
	{
		printf("declare -x %s", env->key);
		if (env->value != NULL)
			printf("=\"%s\"", env->value);
		printf("\n");
	}
}
