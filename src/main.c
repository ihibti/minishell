/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/06/06 01:23:31 by ihibti           ###   ########.fr       */
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
	t_envp	*currentenv;
	t_cmds	*exported;

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
		if (!ret)
			return (printf("porblemooo\n"), 1);
		free(cpy);
		code_attr(ret);
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
		exported = NULL;
		while (current)
		{
			// visualiser = current->name;
			if (ft_strcmp(current->name, "export") == 0)
			{
				exported = current;
				ft_export(current->next, lst);
			}
			printf("char :%s\n", current->name);
			printf("code : %d\n_________\n", current->code_id);
			current = current->next;
		}
		currentenv = *lst;
		if (exported)
			printf("%s\n", exported->name);
		while (currentenv)
		{
			printf("%s=%s\n", currentenv->name, currentenv->value);
			currentenv = currentenv->next;
		}
		free_envp(lst);
		free_tcmd(ret);
	}
	return (0);
}
