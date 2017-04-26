/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:56:35 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/23 15:59:55 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_error(char **cmd_arg)
{
	if (cmd_arg[0] && !ft_strcmp(cmd_arg[0], "exit"))
	{
		if (cmd_arg[1] && cmd_arg[2])
			ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_env *env, char **args)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		env = ptr->next;
		free_env(&ptr);
		ptr = env;
	}
	if (args[1] && !args[2])
		return (ft_atoi(args[1]));
	return (0);
}
