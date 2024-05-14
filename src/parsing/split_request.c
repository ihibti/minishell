/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:19:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/14 21:16:56 by ihibti           ###   ########.fr       */
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

// fonction pour identifer les separateurs;
// 1 pour un separateur 0 pour le reste
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

// fonction similaire a dup mais a une limite pour simplifier le parsing

char	*ft_strlimdup(char *str, int lim)
{
	char	*ret;

	if (!str || !str[0])
		return (NULL);
	ret = ft_strdup(str);
	if (!str)
		return (NULL);
	if (lim >= ft_strlen(ret))
		return (ret);
	ret[lim] = 0;
	return (ret);
}

// fonction principale qui va prendre le resulat de readline
// et va commencer le lexing
// retourne un liste de t_cmd
// retourne null si erreur

t_cmds	**split_token(char *request)
{
	int		i;
	int		j;
	t_cmds	**ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(t_cmds));
	*ret = NULL;
	if (syn_err(request) == 1)
		return (NULL);
	while (request[i])
	{
		while (ft_isspace(request[i]) && request[i])
			i++;
		if (!request[i])
			return (ret);
		while (!ft_isspace(request[i + j]) && request[i + j])
		{
			if (request[i + j] == '\'' || request[i + j] == '"')
			{
				ret = ft_last_tcmd(end_quote(request + i, request[i + j]), 0,
						ret);
				i += j + ft_pos_c(request + i + j + 1, request[i + j]) + 1;
				j = 0;
				break ;
			}
			j++;
		}
		if (j > 0 && request[i])
		{
			ret = ft_last_tcmd(ft_strlimdup(request + i, j + 1), 0, ret);
			i += j;
			j = 0;
		}
		if (!ret)
			return (NULL);
		i++;
	}
	return (ret);
}

// fonction qui va creer un nouveau token avec le string et le code correspondant
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
	return (new);
}

// fonction qui va prendre un char * et un int et qui va ajouter
// a la fin de la liste le nouveau token correspondant
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
	return (list_cmd);
}
