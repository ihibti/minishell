/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:36:27 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/20 22:45:20 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	oper_redir_in(t_cmd *c, int stdin_save)
{
	if (!stdin_save)
		stdin_save = dup(STDIN_FILENO);
	c->redirections->fd = f_open(c->redirections->filename);
	if (c->redirections->fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (errno == ENOENT)
			ft_putstr_fd("no such file or directory: ", 2);
		else if (errno == EACCES)
			ft_putstr_fd("Permission denied: ", 2);
		ft_putstr_fd(c->redirections->filename, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (dup2(c->redirections->fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}

int	oper_redir_out(t_cmd *c, int stdout_save)
{
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	c->redirections->f = f_open2(c->redirections->filename, 12);
	if (!c->redirections->f)
	{
		ft_putstr_fd("minishell: ", 2);
		if (errno == ENOENT)
			ft_putstr_fd("no such file or directory: ", 2);
		else if (errno == EACCES)
			ft_putstr_fd("Permission denied: ", 2);
		ft_putstr_fd(c->redirections->filename, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	c->redirections->fd = fileno(c->redirections->f);
	if (c->redirections->fd == -1)
		return (-1);
	if (dup2(c->redirections->fd, STDOUT_FILENO) == -1)
		return (-1);
	return (stdout_save);
}

int	oper_heredoc_in(t_cmd *c, int stdin_save, t_envp **lst)
{
	int	flag;

	flag = 12;
	if (stdin_save != 0)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			return (-1);
		stdin_save = 0;
		flag = 14;
	}
	if (read_heredoc(c->redirections->filename, flag, lst) == -1)
		return (-1);
	return (exec_heredoc(stdin_save));
}

int	oper_redir_app(t_cmd *c, int stdout_save)
{
	(void)stat;
	if (!stdout_save)
		stdout_save = dup(STDOUT_FILENO);
	c->redirections->f = f_open2(c->redirections->filename, 14);
	if (!c->redirections->f)
	{
		ft_putstr_fd("minishell: ", 2);
		if (errno == ENOENT)
			ft_putstr_fd("no such file or directory: ", 2);
		else if (errno == EACCES)
			ft_putstr_fd("Permission denied: ", 2);
		ft_putstr_fd(c->redirections->filename, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	c->redirections->fd = fileno(c->redirections->f);
	if (c->redirections->fd == -1)
		return (-1);
	if (dup2(c->redirections->fd, STDOUT_FILENO) == -1)
		return (-1);
	return (stdout_save);
}

int	redirec_main(t_cmd	**argument, t_envp **lst)
{
	t_cmd		*c;
	int			return_value;
	int			cpy_stdin_out[2];

	c = (*argument);
	if (!c->redirections)
		return (parsing_command(c, lst));
	cpy_stdin_out[0] = 0;
	cpy_stdin_out[1] = 0;
	while (c && c->redirections)
	{
		if (execute_parsing(c, cpy_stdin_out, lst) == -1)
			return (close_file(c->redirections));
		c->redirections = c->redirections->next;
	}
	return_value = parsing_command(c, lst);
	if (close_file(c->redirections) == -1)
		return (1);
	if (reset_stdin_out(cpy_stdin_out) == -1)
		return (-1);
	return (return_value);
}
