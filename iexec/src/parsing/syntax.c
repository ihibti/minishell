/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:35:10 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/16 14:50:19 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// retourne les erreurs de syntaxe
// 1 pour une erreur 0 si tout va bien

int	syn_err(char *str)
{
	if (!str)
		return (1);
	if (non_print(str) == 1)
		return (1);
	if (open_quote(str) == 1)
		return (1);
	if (tok_acc(str) == 1)
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
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] == '_' || str[i] == '\'' || str[i] == '"')
				return (0);
			if (str[i] == '$' || str[i] == ' ' || str[i] == '?')
				return (0);
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				return (0);
			if (str[i] == '-' || str[i] == '.' || str[i] == '/')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

// fonction qui verifie que chaque quote soit fermee
// 1 si ouverte
// 0 si fermee
// -1 si erreur

int	open_quote(char *str)
{
	int		flag;
	int		i;
	char	quote;

	flag = 0;
	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = 1;
			quote = str[i];
			i++;
			while ((str[i] != quote) && str[i])
				i++;
		}
		if (!str[i])
			return (flag);
		flag = 0;
		i++;
	}
	return (flag);
}

void	advance(char *str, int *i)
{
	int		j;
	char	quote;

	j = *i;
	if (str[j] == '\'' || str[j] == '"')
	{
		quote = str[j++];
		while (str[j] && (str[j] != quote))
			j++;
	}
	*i = j;
}

int	tok_acc(char *str)
{
	int		i;
	int		j;
	char	quote;

	init_0(&i, &j);
	while (str[i])
	{
		advance(str, &i);
		if (is_token(str + i) == 1)
		{
			while (str[i] && is_token(str + i))
			{
				if (str[i] == '|' && j > 0)
					return (1);
				j++;
				i++;
			}
			if (j > 2)
				return (1);
			reset_syn(&i, &j);
		}
		i++;
	}
	return (0);
}
