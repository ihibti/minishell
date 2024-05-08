/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:02:56 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/08 15:07:24 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_occur(char *str, char c)
{
	int i = 0;
	int count;
	if (!str)
		return (0);
    while(str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

