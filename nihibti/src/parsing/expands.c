/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:29:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/12 12:55:09 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	expanding(t_cmds **cmds, t_envp **lst)
{
	t_cmds	*current;
	int		flag;

	flag = 0;
	if (!cmds || !lst || !*cmds)
		return (-1);
	while (flag == 0)
	{
		flag = 1;
		current = *cmds;
		while (current)
		{
			if (nb_expand(current) > 0)
			{
				flag = 0;
				replace_exp(current, lst);
				if (!current->name)
					return (-1);
			}
			current = current->next;
		}
	}
	return (1);
}

int	nb_expand(t_cmds *cmd)
{
	if (!cmd)
		return (-1);
	if (cmd->code_id == 20)
		return (0);
	if (ft_pos_c(cmd->name, '$') == -1)
		return (0);
	return (exp_exception(cmd->name));
}

int	exp_exception(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && (!is_lim_exp(str[i + 1]) || str[i + 1] == '?'))
			count++;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (!str[i])
				return (count);
		}
		i++;
	}
	return (count);
}

int	replace_exp(t_cmds *cmd, t_envp **lst)
{
	int		i;
	char	*s;

	i = 0;
	if (!cmd || !lst)
		return (-1);
	s = cmd->name;
	while (s[i])
	{
		if (s[i] == '$' && ((is_lim_exp(s[i + 1]) == 0) || (s[i + 1] == '?')))
			return (cmd->name = new_expanded(s, s + i, env_match(s + i + 1,
						lst)), 1);
		if (s[i] == '\'' && interpret(s, s + i) == 1)
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (!s[i])
				return (1);
		}
		else
			i++;
	}
	return (1);
}

void	cp_exp_beg(char **str, char **ret, int *j)
{
	int		i;
	char	*sstr;
	char	*rret;

	i = *j;
	sstr = *str;
	rret = *ret;
	while (sstr[i] && sstr[i] != '$')
	{
		rret[i] = sstr[i];
		i++;
	}
	*j = i;
}
