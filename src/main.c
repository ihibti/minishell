/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/20 19:02:26 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds **ret;
	t_cmds *current;

	(void)ac;
	(void)av;
	char *cpy;
	cpy = readline("test");
	ret = split_token(cpy);
	code_attr(ret);
	if (!ret)
		return (printf("porblemooo\n"), 1);
	current = *ret;
	while (current)
	{
		printf("char :%s\n", current->name);
		printf("code : %d\n_________\n", current->code_id);
		current = current->next;
	}

	t_envp **lst;
	lst = lst_env(env);
    expanding(ret,lst);
    current = *ret;
    while (current)
	{
		printf("char :%s\n", current->name);
		printf("code : %d\n_________\n", current->code_id);
		current = current->next;
	}
	

	return (0);
}