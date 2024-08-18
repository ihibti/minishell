/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_request.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:19:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/16 14:37:52 by ihibti           ###   ########.fr       */
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
	if (c == '\t' || c == '\n')
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

// fonction principale qui va prendre le resulat de
// readline
// et va commencer le lexing
// retourne un liste de t_cmd
// retourne null si erreur

t_cmds	**split_token(char *request)
{
	int		i;
	int		j;
	t_cmds	**ret;

	init_1(&i, &j, &ret);
	if (!ret)
		return (NULL);
	*ret = NULL;
	if (syn_err(request) == 1 || !ret)
		return (ft_putendl_fd("syntax error", 2), ret);
	while (request[i])
	{
		if (skip_spcaes(&i, request) == -1)
			return (ret);
		j = go_last_lex(request, i, j);
		ret = ft_last_tcmd(ft_strlimdup(request + i, j), 0, ret);
		reset_sp_tok(&i, &j);
		if (!ret)
			return (free_tcmd(ret), NULL);
		if (!request[i])
			return (ret);
		if (ft_isspace(request[i]))
			i++;
	}
	return (ret);
}

void	reset_sp_tok(int *i, int *j)
{
	*i += *j;
	*j = 0;
}

int	skip_spcaes(int *i, char *request)
{
	while (ft_isspace(request[*i]) && request[*i])
		*i += 1;
	if (!request[*i])
		return (-1);
	return (1);
}
