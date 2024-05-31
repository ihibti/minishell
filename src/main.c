/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/31 01:24:42 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds	**ret;
	t_cmds	*current;
	t_envp	**lst;
	char	*visualiser;
	char	*cpy;

	(void)ac;
	(void)av;
	while (1)
	{
		cpy = readline("minishell: ");
		if (!cpy || ft_strncmp(cpy, "q", 1) == 0)
		{
			free(cpy);
			return (0);
		}
		ret = split_token(cpy);
		free(cpy);
		code_attr(ret);
		if (!ret)
			return (printf("porblemooo\n"), 1);
		current = *ret;
		while (current)
		{
			visualiser = current->name;
			printf("char :%s\n", current->name);
			printf("code : %d\n_________\n", current->code_id);
			current = current->next;
		}
		lst = lst_env(env);
		expanding(ret, lst);
		current = *ret;
		while (current)
		{
			visualiser = current->name;
			printf("char :%s\n", current->name);
			printf("code : %d\n_________\n", current->code_id);
			current = current->next;
		}
		ret = pptreatment(ret);
		current = *ret;
		while (current)
		{
			visualiser = current->name;
			if (ft_strncmp(current->name, "cd", 2) == 0)
				ft_cd(current, lst);
			printf("char :%s\n", current->name);
			printf("code : %d\n_________\n", current->code_id);
			current = current->next;
		}
		free_envp(lst);
		free_tcmd(ret);
	}
	return (0);
}
