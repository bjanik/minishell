/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:20:42 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/26 16:39:22 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_string_tab(char ***tab)
{
	int		i;
	char	**del;

	i = 0;
	if (!tab || !*tab)
		return ;
	del = *tab;
	while (del[i])
	{
		ft_strdel(&del[i]);
		i++;
	}
	ft_memdel((void**)*tab);
}
