/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:56:02 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/20 22:45:27 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	exec(char *command, t_cmd *c)
{
	int	pid;
	int	status;

	g_exit_code = -2;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		execve(command, c->arguments, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		status = check_exec(command, WEXITSTATUS(status), c->command, status);
		free(command);
		return (status);
	}
	return (0);
}

char	*pathfinder(char *cmd, char **path_t)
{
	int		i;
	char	*cmd_temp;
	char	*add_slash;

	if (!path_t)
		return (NULL);
	i = 0;
	add_slash = ft_strjoin("/", cmd);
	if (!add_slash)
		return (0);
	while (path_t[i])
	{
		cmd_temp = ft_strjoin(path_t[i], add_slash);
		if (!cmd_temp)
			return (free(add_slash), NULL);
		if (access(cmd_temp, F_OK) == 0)
			return (free(add_slash), cmd_temp);
		free(cmd_temp);
		i++;
	}
	free(add_slash);
	return (NULL);
}

char	*put_path(char *command, t_envp **lst)
{
	int		i;
	char	**temp_path;
	char	*path;

	i = 0;
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	else
	{
		while (*lst)
		{
			if (ft_strcmp((*lst)->name, "PATH") == 0)
				break ;
			(*lst)->next;
		}
		if (!*lst)
			exit(1);
		temp_path = ft_split((*lst)->value, ':');
		path = pathfinder(command, temp_path);
		i = -1;
		while (temp_path[++i])
			free(temp_path[i]);
		free(temp_path);
	}
	return (path);
}

int	exec_command(t_cmd *c, t_envp **lst)
{
	char	*command;
	int		i;	

	i = 0;
	while (c->arguments[i])
		i++;
	command = put_path(c->command, lst);
	// demander mettre NULL a la fin du argv au moment du parsing
	return (exec(command, c));
}

int	parsing_command(t_cmd *c, t_envp **lst)
{
	if (ft_strcmp(c->command, "echo") == 0)
		return (ft_echo(c));
	else if (ft_strcmp(c->command, "cd") == 0)
		return (ft_cd(c, lst));
	else if (ft_strcmp(c->command, "pwd") == 0)
		return (ft_pwd(c, lst));
	else if (ft_strcmp(c->command, "export") == 0)
		return (ft_export(c, lst));
	else if (ft_strcmp(c->command, "unset") == 0)
		return (ft_unset(lst, c));
	else if (ft_strcmp(c->command, "env") == 0)
		return (ft_env(lst));
	else if (ft_strcmp(c->command, "exit") == 0)
		return (ft_exit(c));
	else
		return (exec_command(c, lst));
	return (0);
}