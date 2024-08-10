/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:04:10 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 14:22:32 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_out2(int pipe_fd[2], t_redir *redir, t_ori *ori)
{
	int	fd_out;

	if (redir->type == REDIR_OUT_S)
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		perror(redir->filename);
		(close(pipe_fd[0]), close(pipe_fd[1]));
		brexit(ori, E_OPEN);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2(fd_out)");
		(close(pipe_fd[0]), close(pipe_fd[1])), close(fd_out);
		brexit(ori, "error dup\n");
	}
	close(fd_out);
}

void	redir_out(int pipe_fd[2], int flag[4], t_redir *redir, t_ori *ori)
{
	t_pars	*current;
	int		i;

	current = *ori->parsee;
	i = 0;
	while (current && (i < flag[2]))
	{
		i++;
		current = current->next;
	}
	if (redir && (redir->type == REDIR_OUT_S || redir->type == REDIR_OUT_D))
		redir_out2(pipe_fd, redir, ori);
	else if (flag[1] != 0 && current->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2(pipe_fd[1])");
			(close(pipe_fd[0]), close(pipe_fd[1]));
			brexit(ori, "error dup\n");
		}
	}
}

void	redir_in2(int pipe_fd[2], int c_fd, t_ori *ori)
{
	if (dup2(c_fd, STDIN_FILENO) == -1)
	{
		perror("dup2(c_fd)");
		(close(pipe_fd[0]), close(pipe_fd[1]), close(c_fd));
		brexit(ori, "error dup\n");
	}
}

void	redir_in(int pipe_fd[2], int flag[4], t_redir *redir, t_ori *ori)
{
	int	fd_in;

	if ((redir) && (redir->type == REDIR_IN_S || redir->type == HEREDOC))
	{
		fd_in = open(redir->filename, O_RDONLY);
		if (fd_in == -1)
		{
			perror(redir->filename);
			(close(pipe_fd[0]), close(pipe_fd[1]), close(flag[3]));
			brexit(ori, E_OPEN);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2(fd_in)");
			(close(pipe_fd[0]), close(pipe_fd[1]), close(flag[3]),
				close(fd_in));
			brexit(ori, E_OPEN);
		}
		close(fd_in);
	}
	else if (flag[0] != 0 && flag[2] != 0)
		redir_in2(pipe_fd, flag[3], ori);
}

void	do_dup(int c_fd, int pipe_fd[2], int i, t_ori *ori)
{
	int		flag[4];
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
	flag[0] = 1;
	flag[1] = 1;
	flag[2] = i;
	flag[3] = c_fd;
	while (redir)
	{
		if (redir->type == REDIR_IN_S || redir->type == HEREDOC)
		{
			redir_in(pipe_fd, flag, redir, ori);
			flag[0] = 0;
		}
		else if (redir->type == REDIR_OUT_S || redir->type == REDIR_OUT_D)
		{
			redir_out(pipe_fd, flag, redir, ori);
			flag[1] = 0;
		}
		redir = redir->next;
	}
	redir_in(pipe_fd, flag, redir, ori);
	redir_out(pipe_fd, flag, redir, ori);
	close_all_fd(pipe_fd, c_fd, i, true);
}
