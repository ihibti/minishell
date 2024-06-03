/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:15:06 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/03 18:40:34 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(t_cmds *cmds, t_cmds **env,t_ori *ori)
{
	if (!env)
		return (1);
    if (!cmds)
        return(print_export(env),0);
    
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
