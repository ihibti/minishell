/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:58:17 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/20 18:43:49 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//fonction qui a pour but de definir la taille de la 
// valeur a expand 

int	is_lim_exp(char c)
{
	if (c == 0 || c == ' ')
		return (1);
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

//fonction qui a pour but de trouver un equivalent de la valeur 
// a expand dans le tableau d'environnement
// retourne null si erreur ou si il n y a 
// pas de valeur correspondante
// retorune la value qui match si il y a un match
t_envp	*env_match(char *str, t_envp **lst)
{
	int i = 0;
	t_envp *current;

	if (!str || !str[0] || !lst)
		return (NULL);
	while (str[i] && is_lim_exp(str[i]) == 0)
		i++;
	current = *lst;
	while (current)
	{
		if (ft_strncmp(str, current->name, i) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}