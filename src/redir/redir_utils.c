/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:34:48 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/29 20:15:57 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_buff(char *buffer, int filenum)
{
	if (filenum == -1)
		return (-1);
	ft_putstr_fd(buffer, filenum);
	ft_putchar_fd('\n', filenum);
	free(buffer);
	return (0);
}
int	put_heredoc(t_envp **env, char *end_str, FILE *temp)
{
	char	*buffer;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			ft_putchar_fd('\n', 1);
			ft_putstr_fd("MINI:  warning: here-document delimited by end-of-file (wanted `",
				2);
			ft_putstr_fd(end_str, 2);
			ft_putstr_fd("')\n", 2);
			exit(f_close2(fileno(temp), temp));
		}
		buffer = expanding_hd(buffer, env);
		if (ft_strncmp(buffer, end_str, ft_strlen(end_str)) == 0)
			break ;
		if (print_buff(buffer, fileno(temp)) == -1)
			exit(-1);
	}
	exit(f_close2(fileno(temp), temp));
}

int	read_heredoc(char *end_str, int flag, t_envp **lst)
{
	FILE	*temp;
	int		pid;
	int		status;

	if (access(TEMP, F_OK) == 0 && unlink(TEMP) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		temp = fopen(TEMP, flag);
		put_heredoc(lst, end_str, temp);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (status == 2)
			printf("\n");
		return (status);
	}
	return (0);
}

int	exec_heredoc(int flag)
{
	FILE	*temp;
	int		stdin_save;
	int		fd;

	temp = fopen(TEMP, 13);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	if (fd == -1)
		return (-1);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	return (stdin_save);
}


int	execute_parsing(t_pars *c, int std_s[], t_envp **lst)
{
	if (c->redirections->type == REDIR_IN_S)
		std_s[0] = ch_err(oper_redir_in(c, std_s[0]), std_s);
	else if (c->redirections->type == REDIR_OUT_S)
		std_s[1] = ch_err(oper_redir_out(c, std_s[1]), std_s);
	else if (c->redirections->type == HEREDOC)
		std_s[0] = ch_err(oper_heredoc_in(c, std_s[0], lst), std_s);
	else if (c->redirections->type == REDIR_IN_S)
		std_s[1] = ch_err(oper_redir_app(c, std_s[1]), std_s);
	if (std_s[0] == -1 || std_s[1] == -1)
		return (-1);
	return (0);
}
