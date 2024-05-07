/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:19:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/07 12:45:29 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	creer une fonction qui va ajouter a la fin de la liste
	un command type :
	elle prendra en parametre le char * de groupe de
	mots en question et int pour le code associe;


	incrementation du pointeur pour le commencement du groupe de mots




*/

char	*ft_strlimdup(char *str, int lim)
{
	char	*ret;

	ret = ft_strdup(str);
	if (!str)
		return (NULL);
	if (lim >= ft_strlen(ret))
		return (ret);
	ret[lim] = 0;
	return (ret);
}

t_cmds	*split_token(char *request)
{
}

t_cmds	*ft_new_tcmd(char *str, int code)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->code_id = code;
	new->name = ft_strdup(str);
	if (!(new->name))
		return (free(new), NULL);
	new->next = NULL;
	new->prev = NULL;
}
t_cmds	*ft_last_tcmd(char *str, int code)
{
}
