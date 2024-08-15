/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:13:09 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 16:35:29 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fork_hd(t_redir *redir, t_ori *ori, char *modified)
{
	pid_t	pid;
	char	*tmp;

	pid = fork();
	if (pid == -1)
		(free(modified), brexit(ori, E_FORK, 1));
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler_here_doc);
		g_exit_code = 0;
		g_exit_code = ft_heredoc(redir, modified, ori);
		if (g_exit_code == -999)
		{
			g_exit_code = 130;
			unlink(modified);
		}
		brexit(ori, NULL, g_exit_code);
	}
	tmp = redir->filename;
	redir->filename = modified;
	free(tmp);
	g_exit_code = wait_for_child(pid);
	return (g_exit_code);
}

int	loop_here2(t_ori *ori, t_redir *redir)
{
	char	*nb;
	char	*f_name;

	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			nb = ft_itoa(ori->nb_heredoc++);
			if (!nb)
				brexit(ori, E_MALLOC, 1);
			f_name = ft_strjoin(HD, nb);
			if (!f_name)
				(free(nb), brexit(ori, E_MALLOC, 1));
			free(nb);
			if (fork_hd(redir, ori, f_name))
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

int	loop_here(t_ori *ori)
{
	char	*nb;
	char	*f_name;
	t_redir	*redir;
	t_pars	*pars;
	int		ret;

	pars = *ori->parsee;
	signal(SIGINT, sigint_handler_child);
	while (pars)
	{
		redir = pars->redirections;
		ret = loop_here2(ori, redir);
		if (ret)
			return (ret);
		pars = pars->next;
	}
	return (0);
}

int	read_hd(t_ori *ori, t_redir *redir, char *mod, int fd)
{
	char	*line;
	char	*mark;

	line = NULL;
	while ("bro is goated")
	{
		if (isatty(0))
			ft_putstr_fd("heredoc > ", 1);
		line = get_next_line(0);
		if (g_exit_code == -999)
			return (free_ret_nul(line), free(mod), close(fd), g_exit_code);
		if (!line || ft_strncmp(line, mod, ft_strlen(line)) == 0)
		{
			if (!line)
				return (ft_putstr_fd(E_HEREDOC, 2), ft_putendl_fd(mod, 2),
					free(mod), close(fd), -1);
			free(line);
			break ;
		}
		mark = line;
		line = expanding_hd(line, ori->envs);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (free(mod), close(fd), 0);
}

int	ft_heredoc(t_redir *redir, char *modified, t_ori *ori)
{
	int		fd;
	char	*eof;

	fd = open(modified, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(modified), brexit(ori, E_OPEN, 1), -1);
	free(modified);
	eof = ft_strjoin(redir->filename, "\n");
	if (!eof)
		return (close(fd), brexit(ori, E_MALLOC, 1));
	return (read_hd(ori, redir, eof, fd));
}
