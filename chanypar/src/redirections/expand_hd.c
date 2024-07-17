/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:03:08 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/17 19:28:20 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nb_expand_hd(char *str)
{
	if (!str)
		return (-1);
	if (ft_pos_c(str, '$') > -1)
		return (1);
	return (0);
}

int	replace_exp_hd(char **stri, t_envp **lst)
{
	int	i;

	i = 0;
    char *str;
    str = *stri;
	if (!str || !lst)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && ((is_lim_exp(str[i + 1]) == 0) || (str[i
					+ 1] == '?')))
			return (*stri = new_expanded(str, str + i, env_match(str + i + 1,
						lst)), 1);
		i++;
	}
	return (1);
}

int	expanding_hd(char *str, t_envp **envp)
{
	int	flag;

	while (nb_expand_hd(str) > 0)
	{
		replace_exp_hd(&str, envp);
		if (!str)
			return (-1);
	}
	return (1);
}

char	*free_ret_nul(char *str)
{
	if (str)
		free(str);
	return (NULL);
}