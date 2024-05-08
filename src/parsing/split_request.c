/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:19:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/07 16:15:36 by ihibti           ###   ########.fr       */
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

char *req_limit(char *str)
{
    
}

t_cmds	*split_token(char *request)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (request[i])
	{
        
		while (ft_isspace(request[i]) == 0)
            i++;
        if (!request[i])
            break;
        i++;
	}
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
