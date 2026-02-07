/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:53 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 21:40:44 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_envval(t_envval *envval, char *envp[])
{
	envval->lst = init_env_list(envp);
	envval->envp = ft_strarrdup(envp);
	envval->is_changed = false;
	envval->exit_code = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_envval	env_val;
	int			res;

	if (!argc || !argv)
		return (0);
	init_envval(&env_val, envp);
	while (1)
	{
		set_terminal(false);
		enroll_custom_signal();
		line = readline("minishell$ ");
		if (!line)
			break ;
		res = parser_handler(line, &env_val);
		free(line);
		if (res == EXIT_CODE)
			break ;
	}
	rl_clear_history();
	ft_lstclear(&env_val.lst, free_env);
	ft_freesplit(env_val.envp);
	return (env_val.exit_code);
}
