/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:43:52 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 15:25:49 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_ori *ori, t_pars *pars)
{
	char	pwd[2048];

	(void)ori;
	(void)pars;
	if (!getcwd(pwd, 2048))
	{
		ft_putstr_fd("PWD error :", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	ft_putstr_fd(pwd, ori->fraude);
	ft_putstr_fd("\n", ori->fraude);
	return (0);
}
