/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:06 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/27 13:19:26 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bad_id(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	if (!str)
		return (1);
	if (!(ft_isalpha(str[0]) || str[i] == '_'))
		return (1);
	if (ft_occur(str, '=') > 1)
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
			&& str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	export_error(char *str)
{
	if (bad_id(str))
		return (1);
	return (0);
}

void	print_export(t_envp *envp)
{
	while (envp)
	{
		if (envp->name && envp->value)
		{
			printf("declare -x %s=", envp->name);
			printf("\"%s\"\n", envp->value);
		}
		else
			printf("declare -x %s\n", envp->name);
		envp = envp->next;
	}
}

t_envp	**add_envpnull(t_envp **ret, char *str)
{
	t_envp	*current;
	t_envp	*new;

	if (!ret || !str)
		return (NULL);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = ft_strdup(str);
	new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->unset = 0;
	if (!*ret)
	{
		*ret = new;
		return (ret);
	}
	current = *ret;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (ret);
}

int	ft_export(t_cmds *cmds, t_envp **env)
{
	char	*str;

	if (!env)
		return (1);
	if (!cmds->next)
		return (0);
	cmds = cmds->next;
	while (cmds)
	{
		str = cmds->name;
		if (!*str || export_error(str))
			return (ft_putstr_fd("mkshell export bad assignment\n", 2), 1);
		if (ft_pos_c(str, '=') == -1)
		{
			if (!add_envpnull(env, str))
				return (-1);
		}
		else
		{
			if (!add_envplast(env, str))
				return (-1);
		}
		cmds = cmds->next;
	}
	return (0);
}
// petit probleme car la fonction de base ne se
// comporte pas comme ailleurs dans le lexing
// a voir
// int	syn_export(char *str)
// {
// 	if (!str)
// 		return (NULL);
// 	int i = 0;
// 	while (ft_isspace(str[i]))
// 		i++;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 			break ;
// 		i++;
// 	}
// 	if (str[i++] != '=')
// 		return (1);
// 	while (str[i])

// }
