/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/16 14:57:15 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_arg_n(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 2;
	if (ft_strlen(str) < 2)
		return (0);
	if (str[0] && str[0] != '-')
		return (0);
	if (str[1] && str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_ori *ori, t_pars *pars)
{
	int	flag;
	int	i;

	if (!pars)
		return (1);
	i = 1;
	if (pars->arguments && pars->arguments[1]
		&& check_arg_n(pars->arguments[1]))
	{
		flag = 0;
		i++;
	}
	else
		flag = 1;
	while (pars && pars->arguments && pars->arguments[i])
	{
		ft_putstr_fd(pars->arguments[i], ori->fraude);
		if (pars->arguments[i] && pars->arguments[i + 1])
			ft_putstr_fd(" ", ori->fraude);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", ori->fraude);
	return (0);
}
