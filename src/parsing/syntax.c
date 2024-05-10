/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:35:10 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/10 17:45:28 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// retourne les erreurs de syntaxe
// 1 pour une erreur 0 si tout va bien

int	syn_err(char *str)
{
	int	i;

	i = 0;
	if (ft_occur(str, '"') % 2 != 0)
		return (1);
	if (ft_occur(str, '\'') % 2 != 0)
		return (1);
	if (non_print(str) == 1)
		return (1);
	return (0);
}

// idem a isprint mais pour un string entier

int	non_print(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str)
	{
		if (ft_isprint(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
