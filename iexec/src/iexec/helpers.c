/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:54 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 18:26:12 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			return (free(add_slash), freee_error(path_t), NULL);
		if (access(cmd_temp, F_OK) == 0)
			return (free(add_slash), freee_error(path_t), cmd_temp);
		free(cmd_temp);
		i++;
	}
	free(add_slash);
	freee_error(path_t);
	return (NULL);
}

char	*put_path(char *command, t_envp **lst)
{
	int i;
	char **temp_path;
	char *path;

	i = 0;
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	else
	{
		while (*lst)
		{
			if (ft_strcmp((*lst)->name, "PATH") == 0)
				break ;
			(*lst) = (*lst)->next;
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