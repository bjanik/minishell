/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:59:11 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/18 15:02:32 by bjanik           ###   ########.fr       */
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

t_shell	*init_minishell(char **environ)
{
	t_shell	*shell;

	if ((shell = (t_shell*)malloc(sizeof(t_shell))) == NULL)
		ft_perror("malloc failed");
	shell->env = dup_env(environ);
	shell->mod_env = NULL;
	shell->envir = NULL;
	shell->cmds = NULL;
	shell->paths = NULL;
	shell->shell_name = "bsh";
	shell->exit_status = 0;
	return (shell);
}
