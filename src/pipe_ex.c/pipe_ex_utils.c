/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:50:38 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/03 15:11:31 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_syntax(t_cmds **cmds)
{
	t_cmds	*current;
	int		flag;

	flag = 0;
	if (!cmds || !*cmds)
		return (0);
	current = *cmds;
	if (current->code_id = PIPE_N)
		return (1);
	while (current)
	{
		if (current->code_id == PIPE_N && !flag)
			flag = 1;
		else if (current->code_id == 0)
			flag = 0;
		else if (current->code_id == 1 && flag)
			return (1);
		current = current->next;
	}
	return (0);
}

// donne le type de la commande.
// -1 si nul 0 si mot 1 si spcial
// exemple pipe redir
int	type_cmd(t_cmds *cmd)
{
	int	i;

	if (!cmd)
		return (-1);
	i = cmd->code_id;
	if (i == WORD || i == SIN_QUOTE || i == DOUB_QUOTE)
		return (0);
	return (1);
}
