/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:14 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/26 21:57:14 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_envp **lst, t_cmds *cmd)
{
	t_envp	*current;

	if (!lst || !cmd)
		return (1);
	if (!cmd->next)
		return (free_envp(lst), 0);
	current = env_match(cmd->next->name, lst);
	if (!current)
		return (0);
	if (current->prev)
		current->prev->next = current->next;
	else
		*lst = current->next;
	if (current->next)
		current->next->prev = current->prev;
	free(current);
	return (0);
}
