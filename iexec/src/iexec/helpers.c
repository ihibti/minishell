/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:25:54 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 16:30:35 by ihibti           ###   ########.fr       */
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
