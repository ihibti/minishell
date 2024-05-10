/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:19:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/10 17:14:01 by ihibti           ###   ########.fr       */
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
int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == 0)
		return (-1);
	return (0);
}

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

// fonction principal

t_cmds	**split_token(char *request)
{
	int		i;
	int		j;
	t_cmds	**ret;

	ret = NULL;
	while (request[i])
	{
        // j = new_tabt        
	}
}

//fonction qui va creer un nouveau token avec le string et le code correspondant
// si erreur retourn null

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


// fonction qui va prendre un char * et un int et qui va ajouter
// a la fin de la liste le nouveau token correspondant
//si erreur  ou pointeur vide retourne null;
// si liste vide va creer nouvelle

t_cmds	*ft_last_tcmd(char *str, int code, t_cmds **list_cmd)
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
    
}
