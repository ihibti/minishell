/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:28:59 by chanypar          #+#    #+#             */
/*   Updated: 2024/08/03 12:24:38 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit_code(t_pars **commands, int exit_code,t_envp **lst)
{
	int	is_exit;

	if (!*commands)
		return;
	is_exit = ft_strcmp((*commands)->command, "exit");
	if (exit_code == 0 && is_exit)
		return ;
	if (!is_exit && exit_code == 0)
	{
        free_envp(lst);
        free(lst);
		exit(exit_code);
	}
}

int	convert_code(int num)
{
	if (num == 255 || num == -1)
		return (1);
	return (num);
}
