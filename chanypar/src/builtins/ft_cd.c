/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:44:17 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/30 16:31:59 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_pars *pars, t_envp **lst)
{
	int		i;
	char	**dict;
	char	new_pwd[2048];

	i = 0;
	if (!pars)
		return (ft_putstr_fd("erreur cd\n", 2), 1);
	dict = pars->arguments;
	while (dict[i])
		i++;
	if (i != 2)
		return (ft_putstr_fd("cd : too many arguments\n", 2), 1);
	if (chdir(dict[1]) == -1)
		return (ft_putstr_fd("cd : No such file or directory\n", 2), 1);
	if (!getcwd(new_pwd, 2048))
		return (1);
	update_env(lst, "PWD", new_pwd);
	return (0);
}
