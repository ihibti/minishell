/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:14 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 16:18:32 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_one_env(t_envp *env, t_envp **lst)
{
	if (!env)
		return ;
	if (!env->prev)
		*lst = env->next;
	if (env->prev)
		env->prev->next = env->next;
	if (env->next)
		env->next->prev = env->prev;
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	free(env);
}

int	ft_unset(t_ori *ori, t_pars *pars)
{
	char	**str;
	t_envp	*current;
	t_envp	**lst;
	int		i;

	lst = ori->envs;
	if (!lst || !pars)
		return (1);
	str = pars->arguments;
	if (!str[1])
		return (free_envp(lst), 0);
	i = 1;
	while (str[i])
	{
		current = env_match(str[i], lst);
		if (current)
			free_one_env(current, lst);
		i++;
	}
	return (0);
}
