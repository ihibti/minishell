/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iexecori.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:46:55 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 18:22:58 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	safe_close(int fd)
{
	if (fd > 1)
		close(fd);
}

void	close_fd(int fd, int i)
{
	if (i > 1)
		close(fd);
}

void	close_all_fd(int pipe_fd[2], int c_fd, int i, bool close_fd_0)
{
	if (close_fd_0 == true)
		close(pipe_fd[0]);
	close_fd(c_fd, i);
	close(pipe_fd[1]);
}

// TODO : changer pour avoir en parametres le __msg___

int	brexit(t_ori *ori, char *msg, int exitc)
{
	if (msg)
	{
		printf("error lign %d, in file%s\n", __LINE__, __FILE__);
		printf("%s\n", msg);
	}
	free_ori(ori);
	exit(exitc);
}

int	nb_pipes(t_pars *current)
{
	int	i;

	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	is_dir(char *cmd)
{
	struct stat	statbuf;

	if (lstat(cmd, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

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
	if (get_built_func(*ori->parsee))
	{
		g_exit_code = do_built(ori, LEGIT, *ori->parsee);
		brexit(ori, NULL, g_exit_code);
	}
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

int	count_node_env(t_envp **env)
{
	int		i;
	t_envp	*current;

	i = 0;
	current = *env;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (s1 == NULL)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	ret = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
			* sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

char	**env_trans(t_envp **lst)
{
	char	**result;
	int		i;
	char	*pre;
	t_envp	*env;

	env = *lst;
	result = malloc(sizeof(char *) * (count_node_env(lst) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (env)
	{
		pre = ft_strjoin_env("=", env->value);
		if (!pre)
			return (freee_error(result), NULL);
		result[i] = ft_strjoin_env(env->name, pre);
		if (!result[i])
			return (freee_error(result), free(pre), NULL);
		free(pre);
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}

int	pipex(t_ori *ori)
{
	int		fd[2];
	pid_t	pid;
	int		flag;
	t_pars	*current;
	int		i;

	i = 0;
	flag = -1;
	current = *ori->parsee;
	while (current)
	{
		if (i != 0)
			flag = fd[0];
		if (pipe(fd) == -1)
			return (close_all_fd(fd, flag, i, true), brexit(ori, E_PIPE, 1),
				-1);
		pid = fork();
		if (pid == -1)
			return (close_all_fd(fd, flag, i, true), brexit(ori, E_FORK, 1),
				-1);
		if (pid == 0)
			child(ori, fd, i, flag);
		close_all_fd(fd, flag, i, false);
		i++;
		current = current->next;
	}
	close_all_fd(fd, flag, i, true);
	g_exit_code = wait_for_child(pid);
	return (0);
}
