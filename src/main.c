/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/10 20:37:04 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av)
{
	t_cmds **ret;
	t_cmds *current;

	(void)ac;
	(void)av;
	char *cpy;
	cpy = readline("test");
	ret = split_token(cpy);
	if (!ret)
		return (printf("porblemooo\n"), 1);
	current = *ret;
	while (current)
	{
		printf("char :%s\n_________\n", current->name);
		current = current->next;
	}
	return (0);
}