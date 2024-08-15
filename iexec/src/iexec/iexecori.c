/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iexecori.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:46:55 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 16:55:43 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_msg(char *path, char **cmd, char **env, t_ori *ori)
{
	int	status;

	status = 1;
	ft_putstr_fd(cmd[0], 2);
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (is_dir(cmd[0]))
			(ft_putendl_fd(": Is a directory", 2), status = 126);
		else if (access(cmd[0], F_OK) == -1)
			(ft_putendl_fd(": No such file or directory", 2), status = 127);
		else if (access(cmd[0], X_OK | R_OK) == -1)
			(ft_putendl_fd(": Permission denied", 2), status = 126);
	}
	else
	{
		if (!path)
			(ft_putendl_fd(": command not found", 2), status = 127);
		else if (ft_strcmp(path, "NULL") == 0)
			(ft_putendl_fd(": No such file or directory", 2), status = 127);
		else if (access(path, X_OK) == -1)
			(ft_putendl_fd(": Permission denied", 2), status = 126);
	}
	(free(path), freee_error(env));
	free_ori(ori);
	exit(status);
}

void	ft_exec(char **cmd, char **env, t_ori *ori)
{
	int		i;
	char	*path;
	char	**tmp_path;

	tmp_path = NULL;
	path = NULL;
	i = 0;
	if (ft_strchr(cmd[0], '/') != NULL && access(cmd[0], F_OK) == 0)
		path = ft_strdup(cmd[0]);
	else if (ft_strchr(cmd[0], '/') == NULL && env[i])
	{
		while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
			i++;
		if (env[i])
			tmp_path = ft_split(&env[i][5], ':');
		if (!tmp_path)
			error_msg(ft_strdup("NULL"), cmd, env, ori);
		path = pathfinder(cmd[0], tmp_path);
	}
	if (!path)
		error_msg(path, cmd, env, ori);
	execve(path, cmd, env);
	error_msg(path, cmd, env, ori);
}

void	child(t_ori *ori, int fd[2], int i, int flag)
{
	t_pars	*current;
	int		j;
	char	**env;

	signal(SIGINT, &sigint_handler_child);
	j = 0;
	current = *ori->parsee;
	while (j < i && current)
	{
		current = current->next;
		j++;
	}
	do_dup(flag, fd, i, ori);
	close_all_fd(fd, flag, i, true);
	if (get_built_func(current))
	{
		g_exit_code = do_built(ori, LEGIT, current);
		brexit(ori, NULL, g_exit_code);
	}
	if (!current->arguments)
		brexit(ori, NULL, 0);
	env = env_trans(ori->envs);
	if (!env)
		brexit(ori, E_MALLOC, 1);
	ft_exec(current->arguments, env, ori);
}

int	wait_for_child(pid_t pid)
{
	int		status[2];
	pid_t	r_waitpid;

	while (1)
	{
		r_waitpid = waitpid(-1, &status[0], 0);
		if (r_waitpid == -1)
			break ;
		if (r_waitpid == pid)
			status[1] = status[0];
	}
	if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));
	else if (WIFSIGNALED(status[1]))
	{
		if (WTERMSIG(status[1]) + 128 == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (WTERMSIG(status[1]) + 128 == 130)
			ft_putstr_fd("\n", 2);
		return (WTERMSIG(status[1]) + 128);
	}
	return (0);
}

int	pipex(t_ori *ori)
{
	int		fd[2];
	pid_t	pid;
	int		flag;
	t_pars	*current;
	int		i;

	current = init_pipex(ori, &i, &flag);
	while (current)
	{
		if (i != 0)
			flag = fd[0];
		if (pipe(fd) == -1)
			return (close_all_fd(fd, flag, i, true), brexit(ori, E_PIPE, 1));
		pid = fork();
		if (pid == -1)
			return (close_all_fd(fd, flag, i, true), brexit(ori, E_FORK, 1));
		if (pid == 0)
			child(ori, fd, i, flag);
		close_all_fd(fd, flag, i, false);
		i++;
		current = current->next;
	}
	(close_all_fd(fd, flag, i, true), g_exit_code = wait_for_child(pid));
	return (0);
}
