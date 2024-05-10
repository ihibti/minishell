/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:02:56 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/10 17:08:54 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_occur(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*quote_tok(char *str, int *ind, char quote)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (*ind < 0)
		return (NULL);
	while (str[*ind + i])
	{
		if (str[*ind + i] == quote)
			return (*ind += i, ft_strlimdup(&str[*ind], i));
		i++;
	}
	return (NULL);
}

