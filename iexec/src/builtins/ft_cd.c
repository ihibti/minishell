/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:44:17 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 18:03:56 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_ori *ori, t_pars *pars)
{
	int		i;
	t_envp	*home;
	t_envp	**lst;
	char	new_pwd[2048];

	lst = ori->envs;
	i = 0;
	if (!pars)
		return (ft_putstr_fd("erreur cd\n", 2), 1);
	while (pars->arguments[i])
		i++;
	if (i == 1)
	{
		home = env_match("HOME", lst);
		if (chdir(home->value) == -1)
			return (ft_putstr_fd("cd : No such file or directory\n", 2), 1);
	}
	else if (i > 2)
		return (ft_putstr_fd("cd : too many arguments\n", 2), 1);
	else if (chdir(pars->arguments[1]) == -1)
		return (ft_putstr_fd("cd : No such file or directory\n", 2), 1);
	if (!getcwd(new_pwd, 2048))
		return (1);
	update_env(lst, "PWD", new_pwd);
	return (0);
}
