/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iexec_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:57:38 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 17:10:33 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*replace_exp_hd(char **stri, t_envp **lst)
{
	int		i;
	char	*str;

	i = 0;
	str = *stri;
	if (!str || !lst)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && ((is_lim_exp(str[i + 1]) == 0) || (str[i
					+ 1] == '?')))
			return (new_expanded_hd(str, str + i, env_match(str + i + 1, lst)));
		i++;
	}
	return (str);
}

char	*expanding_hd(char *str, t_envp **envp)
{
	char	*temp;

	while (nb_expand_hd(str) > 0)
	{
		temp = str;
		str = replace_exp_hd(&str, envp);
		if (!str)
			return (NULL);
		temp = free_ret_nul(temp);
	}
	return (str);
}

char	*free_ret_nul(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

void	exec_loop(t_ori *ori)
{
	if (loop_here(ori))
	{
		free_tori(ori);
		return ;
	}
	built_ex(ori);
}
