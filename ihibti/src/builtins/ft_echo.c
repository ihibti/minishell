/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/26 15:59:37 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(t_cmds *current, t_status *status)
{
	printf("%s", current->name);
}

int	ft_echo(t_cmds *cmd, t_cmds **ret)
{
	int			flag;
	t_cmds		*current;
	t_status	*status;

	if (!cmd)
		return (1);
	current = cmd->next;
	status = (*ret)->status;
	if (cmd && ft_strcmp(cmd->name, "-n") == 0)
	{
		flag = 0;
		current = cmd->next;
	}
	else
		flag = 1;
	while (current && (current->code_id == 9 || (current->code_id >= 20
				&& current->code_id != 22)))
	{
		execute(current, status);
		current = current->next;
		if (current)
			printf(" ");
	}
	if (flag == 1)
		printf("\n");
	return (0);
}
