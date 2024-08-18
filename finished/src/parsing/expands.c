/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:29:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/16 16:29:38 by ihibti           ###   ########.fr       */
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
		if (str[i] == '$' && cond_helper(str, i))
			count++;
		if (str[i] == '\'' && interpret(str, str + i) == 1)
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
	char	*str;

	i = 0;
	if (!cmd || !lst)
		return (-1);
	str = cmd->name;
	while (str[i])
	{
		if (str[i] == '$' && (cond_helper(str, i)))
			return (cmd->name = new_expanded(str, str + i, env_match(str + i
						+ 1, lst)), 1);
		if (str[i] == '\'' && interpret(str, str + i) == 1)
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (1);
		}
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
		if (sstr[i] == '\'' && interpret(sstr, sstr + i) == 1)
		{
			rret[i] = sstr[i];
			i++;
			while (sstr[i] && sstr[i] != '\'')
			{
				rret[i] = sstr[i];
				i++;
			}
		}
		rret[i] = sstr[i];
		i++;
	}
	*j = i;
}
