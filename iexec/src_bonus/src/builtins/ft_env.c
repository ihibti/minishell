/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:47:18 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 17:21:10 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_ori *ori, t_pars *pars)
{
	t_envp	*current;
	t_envp	**lst;

	if (!ori)
		return (1);
	lst = ori->envs;
	if (!lst)
		return (1);
	current = *lst;
	while (current)
	{
		ft_putstr_fd(current->name, ori->fraude);
		ft_putstr_fd("=", ori->fraude);
		ft_putstr_fd(current->value, ori->fraude);
		ft_putstr_fd("\n", ori->fraude);
		current = current->next;
	}
	return (0);
}
