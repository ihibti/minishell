/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:03:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/20 21:24:18 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef enum s_type_redir
{
	REDIR_IN_S,
	REDIR_OUT_S,
	REDIR_OUT_D,
	HEREDOC,
}					e_type_redir;

typedef struct s_redir
{
	e_type_redir	type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_pars
{
	char			*command;
	char			**arguments;
	t_redir			*redirections;
	struct s_pars	*next;
}					t_pars;

t_redir	*new_redir(e_type_redir type, char *filename)
{
	t_redir	*res;

	res = malloc(sizeof(t_redir));
	res->type = type;
	res->filename = filename;
	res->next = NULL;
	return (res);
}

t_pars	*parser(t_cmds *cmds)
{
	t_cmds	*current;
	t_pars	*ret;

	ret = malloc(sizeof(t_pars));
	if (!ret)
		return (NULL);
    while(cmds)
    {
        
    }
}



void	add_last_par(t_pars **pars, t_pars *new)
{
	t_pars	*current;

	if (!pars || !new)
		return ;
	if (!*pars)
	{
		*pars = new;
		return ;
	}
	current = *pars;
	while (current->next)
		current = current->next;
	current->next = new;
}
