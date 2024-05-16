/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/16 20:55:28 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmds **ret;
	t_cmds *current;
	int flag = -1;

	(void)ac;
	(void)av;
	char *cpy;
	cpy = readline("test");
	ret = split_token(cpy);
	flag = code_attr(ret);
	if (!ret || flag == -1)
		return (printf("porblemooo\n"), 1);
	current = *ret;
	while (current)
	{
		printf("char :%s\n", current->name);
		printf("code : %d\n_________\n", current->code_id);
		current = current->next;
	}
	flag = 0;
	while (env[flag])
	{
		printf("%s\n___________|\n", env[flag]);
		flag++;
	}

	return (0);
}