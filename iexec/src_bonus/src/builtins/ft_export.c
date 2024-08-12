/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:06 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 17:19:59 by ihibti           ###   ########.fr       */
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
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
			&& str[i] != ' ')
			return (1);
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (0);
}

int	export_error(char *str)
{
	if (ft_occur(str, '=') > 1)
		return (1);
	if (bad_id(str))
		return (1);
	return (0);
}

void	print_export(t_envp *envp, t_ori *ori)
{
	while (envp)
	{
		if (envp->name && envp->value)
		{
			ft_putstr_fd("declare -x ", ori->fraude);
			ft_putstr_fd(envp->name, ori->fraude);
			ft_putstr_fd("=", ori->fraude);
			ft_putstr_fd("\"", ori->fraude);
			ft_putstr_fd(envp->value, ori->fraude);
			ft_putstr_fd("\"\n", ori->fraude);
		}
		else
		{
			ft_putstr_fd("declare -x ", ori->fraude);
			ft_putstr_fd(envp->name, ori->fraude);
			ft_putstr_fd("\n", ori->fraude);
		}
		envp = envp->next;
	}
}

int	ft_export(t_ori *ori, t_pars *pars)
{
	char	**str;
	t_envp	**env;
	int		i;

	i = 1;
	env = ori->envs;
	if (!env || !pars)
		return (1);
	str = pars->arguments;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!str[i] || !str[i][0] || export_error(str[i]))
			return (ft_putstr_fd("mkshell export bad assignment\n", 2), 1);
		if (ft_occur(str[i], '=') > 0)
			if (!add_envplast(env, str[i]))
				return (-1);
		if (ft_occur(str[i], '=') == 0)
			if (!add_envplast_null(env, str[i]))
				return (-1);
		i++;
	}
	return (0);
}
