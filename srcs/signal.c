/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 14:32:17 by bjanik            #+#    #+#             */
/*   Updated: 2017/05/19 13:58:52 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_pid;

void	ft_sighandler(int signum)
{
	if (signum == SIGINT)
		ft_printf("\n");
	if (!g_pid)
		minishell_prompt();
}
