/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/22 16:08:09 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds **ret;
	t_cmds *current;
	t_envp **lst;
	char *visualiser;

	(void)ac;
	(void)av;
	char *cpy;
	while (1)
	{
		cpy = readline("minishell: ");
		if (!cpy || ft_strncmp(cpy, "q", 1) == 0)
			break ;
		ret = split_token(cpy);
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
		free_envp(lst);
		free_tcmd(ret);
	}

	return (0);
}