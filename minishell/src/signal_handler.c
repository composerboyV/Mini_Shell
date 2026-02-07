/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:04:53 by junkwak           #+#    #+#             */
/*   Updated: 2025/01/07 21:41:15 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	print_sigmsg(unsigned char exit_code)
{
	if (exit_code - 128 == SIGINT)
		printf("^C\n");
	if (exit_code - 128 == SIGQUIT)
		printf("^Quit (core dumped)\n");
}

void	set_sigall(t_bool is_ign)
{
	if (is_ign)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_terminal(t_bool c_lflag)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (c_lflag)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enroll_custom_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
