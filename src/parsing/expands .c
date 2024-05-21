/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands .c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:29:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/21 18:24:52 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
creer une fonction qui a la ide d utils
va lire dans les double quotes et les words si il faut
les $"" par des valeurs

*/

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
			}
			current = current->next;
		}
	}
	return (1);
}
// fonction qui donne le nombre d expands
// dans une commande
// -1 si erreur

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

// fonction qui a pour but de trouver le nombre
// d'expands a realiser pour la string
// retourne -1 en cas d erreur
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
		if (str[i] == '$' && !is_lim_exp(str[i + 1]))
			count++;
		if (str[i] == '\'')
		{
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
		if (str[i] == '$')
		{
			cmd->name = new_expanded(str, str + i, i, env_match(str + i + 1,
						lst));
			printf("%s\n", cmd->name);
			return (1);
		}
		if (str[i] == '\'' && cmd->code_id != DOUB_QUOTE)
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (1);
		}
		else
			i++;
	}
	return (1);
}

char	*new_expanded(char *str, char *ptr, int i, t_envp *match)
{
	char	*ret;
	char	*cp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!str || !ptr)
		return (NULL);
	if (is_lim_exp(str[i + 1]) == 1)
		return (str);
	if (!match)
		return (nomatch(ptr, str));
	ret = malloc(ft_strlen(str) + ft_strlen(match->value) + 1);
	while (str[j] && str[j] != '$')
	{
		ret[j] = str[j];
		j++;
	}
	cp = match->value;
	while (cp[k])
		ret[j++] = cp[k++];
	while (*ptr && is_lim_exp(*ptr) == 0)
		ptr++;
	while (*ptr)
	{
		ret[j++] = *ptr;
		ptr++;
	}
	ret[j] = 0;
	return (ret);
}

char	*nomatch(char *ptr, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ptr[i] && !is_lim_exp(ptr[i]))
		i++;
	while (ptr[i])
		ptr[j++] = ptr[i++];
	ptr[j] = 0;
	return (str);
}
