/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:13:46 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/29 20:20:36 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_pipes(t_pars **commands)
{
	int		i;
	t_pars	*current;

	i = 0;
	current = (*commands);
	while (current->next)
	{
		current = current->next;
		i++;
	}
	return (i);
}
