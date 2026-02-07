/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:32:16 by dukim             #+#    #+#             */
/*   Updated: 2024/12/26 13:32:17 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BULITIN_H

# include "../../inc/minishell.h"

int		ft_cd(char **args, t_list *env_list);
int		ft_export(char **args, t_envval *env_val);
int		ft_env(char **args, t_list *env_list);
int		ft_pwd(t_envval *env_val);
int		ft_unset(char **args, t_envval *env_val);
int		ft_echo(char **args);

#endif
