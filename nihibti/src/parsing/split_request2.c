/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_request2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:18:11 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/12 12:49:03 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// fonction qui va creer un nouveau token
// avec le string et le code correspondant
// si erreur retourn null
t_cmds	*ft_new_tcmd(char *str, int code)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->code_id = code;
	new->name = str;
	if (!(new->name))
		return (free(new), NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// fonction qui va prendre un char *
// et un int et qui va ajouter
// a la fin de la liste le nouveau
// token correspondant
// si erreur  ou pointeur vide retourne null;
// si liste vide va creer nouvelle

t_cmds	**ft_last_tcmd(char *str, int code, t_cmds **list_cmd)
{
	t_cmds	*current;
	t_cmds	*new;

	current = NULL;
	new = NULL;
	if (!list_cmd)
		return (NULL);
	if (!*list_cmd)
	{
		*list_cmd = ft_new_tcmd(str, code);
		return (list_cmd);
	}
	new = ft_new_tcmd(str, code);
	if (!new)
		return (NULL);
	current = *list_cmd;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	new->next = NULL;
	return (list_cmd);
}
