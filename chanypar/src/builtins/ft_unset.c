/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:14 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/30 16:27:52 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_envp **lst, t_pars *pars)
{
	char	**str;
	t_envp	*current;
	int		i;

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