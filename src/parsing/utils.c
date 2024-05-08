/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:02:56 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/08 23:11:15 by ihibti           ###   ########.fr       */
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

char	*quote_tok(void)