/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:09:47 by dukim             #+#    #+#             */
/*   Updated: 2025/01/07 21:46:50 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>

# include "../libft/libft.h"

# define EXIT_CODE -1

typedef enum e_bool
{
	false = 0,
	true
}		t_bool;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_envvalue
{
	t_list			*lst;
	char			**envp;
	t_bool			is_changed;
	unsigned char	exit_code;
}	t_envval;

// utils -signal
void	print_sigmsg(unsigned char exit_code);
void	set_sigall(t_bool is_ign);
void	set_terminal(t_bool c_lflag);
void	enroll_custom_signal(void);

// env utils
char	*ft_getenv(const char *env, t_list *env_list);
void	replace_envvalue(const char *env, char *replace, t_list *env_list);
t_list	*init_env_list(char **envp);
void	free_env(void *ptr);
void	export_print(t_list *ptr);

// ft_utils
t_bool	is_quote_ch(char ch);
char	**ft_lst_toarray(t_list *lst);
char	**ft_strdivide(char *str, int c);

// error utils
void	print_stderr(const char *str1, const char *str2);
void	print_exporterr_ch(char ch);
void	print_exporterr_str(char *str);

// builtins
t_bool	is_builtin_cmd(char *cmd);
int		builtin_handler(void *ptr, t_envval *env_val);
int		ft_exit(char **args, t_bool is_child);

// parser
int		parser_handler(char *line, t_envval *env_val);

// exports module
t_list	*tokenize(char *line, t_envval *env_val);
void	free_token(void *ptr);
void	token_tocmdunit(t_list *tokenlst, t_list **cmdunit_list);
void	excute_handler(t_list *cmdlst, size_t cmdlst_len, \
							int *res, t_envval *env_val);
void	free_command(void *ptr);

#endif
