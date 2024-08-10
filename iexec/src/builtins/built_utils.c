/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:21:39 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 18:20:19 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	update_env(t_envp **lst, char *key, char *n_value)
{
	t_envp	*current;

	if (!lst || !key)
		return (-1);
	current = *lst;
	while (current)
	{
		if (!ft_strcmp(key, current->name))
		{
			free(current->value);
			current->value = ft_strdup(n_value);
			return (0);
		}
		current = current->next;
	}
	return (0);
}

void	*get_built_func(t_pars *current)
{
	if (!current)
		return (NULL);
	if (!current->command)
		return (NULL);
	if (ft_strcmp(current->command, "echo") == 0)
		return (&ft_echo);
	else if (ft_strcmp(current->command, "cd") == 0)
		return (&ft_cd);
	else if (ft_strcmp(current->command, "pwd") == 0)
		return (&ft_pwd);
	else if (ft_strcmp(current->command, "export") == 0)
		return (&ft_export);
	else if (ft_strcmp(current->command, "unset") == 0)
		return (&ft_unset);
	else if (ft_strcmp(current->command, "env") == 0)
		return (&ft_env);
	else if (ft_strcmp(current->command, "exit") == 0)
		return (&ft_exit);
	return (NULL);
}

int	do_built(t_ori *ori, int soul, t_pars *current)
{
	t_redir	*redir;
	int		(*fnct_ptr)(t_ori * ori, t_pars * pars);

	fnct_ptr = (int (*)(t_ori * ori, t_pars
				* pars)) get_built_func(*ori->parsee);
	if (soul == LEGIT || !current->redirections)
	{
		ori->fraude = 1;
		return (fnct_ptr(ori, *ori->parsee));
	}
	redir = current->redirections;
	while (redir)
	{
		if (redir->type == REDIR_IN_S || redir->type == HEREDOC)
		{
			ori->fraude_in = open(redir->filename, O_RDONLY);
			if (ori->fraude == -1)
				return (perror(redir->filename), 1);
			close(ori->fraude_in);
		}
		else if (redir->type == REDIR_OUT_S || redir->type == REDIR_OUT_D)
		{
			if (ori->fraude != 1)
				close(ori->fraude);
			if (redir->type == REDIR_OUT_S)
				ori->fraude = open(redir->filename,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				ori->fraude = open(redir->filename,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (ori->fraude == -1)
				return (perror(redir->filename), 1);
		}
		redir = redir->next;
	}
	g_exit_code = fnct_ptr(ori, current);
	return (safe_close(ori->fraude), g_exit_code);
}

void	built_ex(t_ori *ori)
{
	t_pars *current;

	if (count_pipes(ori->parsee) == 0 && get_built_func(*ori->parsee))
		g_exit_code = do_built(ori, FRAUDE, *ori->parsee);
	else
		pipex(ori);
}