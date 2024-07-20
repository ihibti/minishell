/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:32:22 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/20 14:46:31 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_buff(char *buffer, int filenum)
{
	if (filenum == -1)
		return (-1);
	ft_putstr_fd(buffer, filenum);
	ft_putchar_fd('\n', filenum);
	if (buffer)
		free(buffer);
	return (0);
}
int	put_heredoc(t_envp **env, char *end_str, t_file **file, FILE *temp)
{
	char	*buffer;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		buffer = NULL;
		buffer = readline(">");
		if (!buffer)
		{
			ft_putchar_fd('\n', 1);
			ft_putstr_fd("MINI:  warning: here-document delimited by end-of-file (wanted `",
				2);
			ft_putstr_fd(end_str, 2);
			ft_putstr_fd("')\n", 2);
			exit(f_close2(fileno(temp), file, temp));
		}
		buffer = expanding_hd(buffer, env);
		if (ft_strncmp(buffer, end_str, ft_strlen(end_str)) == 0)
			break ;
		if (print_buff(buffer, fileno(temp)) == -1)
			exit(-1);
	}
	exit(f_close2(fileno(temp), file, temp));
}
int	read_heredoc(char *end_str, t_file **file, int flag, t_envp **env)
{
	FILE	*temp;
	int		pid;
	int		status;

	if (access(TEMP, F_OK) == 0 && unlink(TEMP) != 0)
		return (-1);
	temp = f_open2(TEMP, file, flag);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		put_heredoc(env, end_str, file, temp);
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

int	exec_heredoc(t_file **file, int flag)
{
	FILE	*temp;
	int		stdin_save;
	int		fd;

	temp = f_open2(TEMP, file, 13);
	if (!temp)
		return (-1);
	fd = fileno(temp);
	if (fd == -1)
		return (-1);
	if (!flag)
		stdin_save = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	(*file)->f = temp;
	return (stdin_save);
}
