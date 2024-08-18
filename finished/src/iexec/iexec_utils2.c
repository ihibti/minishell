/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iexec_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:28:06 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 16:55:38 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_dir(char *cmd)
{
	struct stat	statbuf;

	if (lstat(cmd, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

t_redir	*init_dodup(t_ori *ori, int i)
{
	t_pars	*current;
	t_redir	*redir;
	int		j;

	j = 0;
	current = *ori->parsee;
	while (j < i)
	{
		current = current->next;
		j++;
	}
	redir = current->redirections;
	return (redir);
}

t_pars	*init_pipex(t_ori *ori, int *i, int *flag)
{
	*i = 0;
	*flag = -1;
	return (*ori->parsee);
}
