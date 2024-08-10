/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:41:41 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 16:37:28 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
		{
			i++;
			continue ;
		}
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_atoi(arg) == -1 || check_numeric(arg))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	while (arg[i] && ((arg[i] >= '0' && arg[i] <= '9') || (arg[0] == '+'
				|| arg[0] == '-')))
		i++;
	if (!arg[i])
	{
		i = ft_atoi(arg);
		if (i < 0)
			i = 256 + i;
		else if (i > 256)
			i = i - 256;
	}
	return (i);
}

int	ft_exit(t_ori *ori, t_pars *pars)
{
	int	rv;

	rv = 0;
	if (pars->arguments && pars->arguments[0] && !pars->arguments[1])
		return (brexit(ori, NULL, 0));
	else if (pars->arguments && pars->arguments[0] && pars->arguments[1])
	{
		if (pars->arguments[1])
		{
			ft_putstr_fd("exit: too many arguments", 2);
			return (-1);
		}
		rv = check_arg(pars->arguments[1]);
		if (rv)
			return (rv);
	}
	return (0);
}
