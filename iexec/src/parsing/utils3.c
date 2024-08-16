/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:53:30 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/16 14:56:09 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	go_last_lex(char *str, int i, int j)
{
	if (is_token(str + i + j))
	{
		while (str[i + j] && (str[i + j] == str[i]))
			j++;
		return (j);
	}
	while (str[i + j] && !ft_isspace(str[i + j]) && !is_token(str + i + j))
	{
		if (str[i + j] == '\'' || str[i + j] == '"')
			j = n_end_quote(str, i, j) + 1;
		else
			j++;
	}
	return (j);
}

int	is_token(char *str)
{
	if (!str)
		return (0);
	if (!*str)
		return (0);
	if (ft_strncmp("<", str, 1) == 0 || ft_strncmp(">", str, 1) == 0)
		return (1);
	if (ft_strncmp("|", str, 1) == 0)
		return (1);
	return (0);
}

int	n_end_quote(char *str, int i, int j)
{
	char	c;

	c = str[i + j];
	j++;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

void	free_tcmd(t_cmds **cmds)
{
	t_cmds	*current;
	t_cmds	*tmp;

	if (!cmds)
		return ;
	if (!*cmds)
	{
		free(cmds);
		cmds = NULL;
		return ;
	}
	current = *cmds;
	while (current)
	{
		tmp = current->next;
		free(current->name);
		free(current);
		current = tmp;
	}
	free(cmds);
	cmds = NULL;
}
