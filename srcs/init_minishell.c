/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:59:11 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/26 15:27:05 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*dup_env(char **environ)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (environ[i])
	{
		if (!env)
			env = create_node(environ[i++]);
		else
			push_back_env(&env, environ[i++]);
	}
	return (env);
}

void	init_minishell(t_shell *shell)
{
	shell->env = dup_env(environ);
	shell->mod_env = NULL;
	shell->envir = NULL;
	shell->cmd = NULL;
	shell->paths = NULL;
	shell->shell_pid = getpid();
	shell->shell_name = "bsh";
	shell->exit_status = 0;
	shell->ret = 0;
}
