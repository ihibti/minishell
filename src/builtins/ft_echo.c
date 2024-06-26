/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/30 20:50:31 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmds *cmd)
{
	int		flag;
	t_cmds	*current;

	if (!cmd)
		return (1);
	current = cmd;
	current = cmd->next;
	if (ft_strcmp(cmd->name, "-n") == 0)
	{
		flag = 1;
		current = current->next;
	}
	else
		flag = 0;
	while (current)
	{
		printf("%s", current->name);
		if (current->next)
			printf(" ");
		current = current->next;
	}
	if (flag == 1)
		printf("\n");
}
