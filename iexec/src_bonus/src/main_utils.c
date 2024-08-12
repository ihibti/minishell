/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:28:59 by chanypar          #+#    #+#             */
/*   Updated: 2024/08/10 14:06:17 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit_code(t_pars **commands, int exit_code, t_envp **lst,
		t_ori *ori)
{
	int	is_exit;

	if (!*commands || !(*commands)->command)
		return ;
	is_exit = ft_strcmp((*commands)->command, "exit");
	if (exit_code == 0 && is_exit)
		return ;
	if (!is_exit)
	{
		free_envp(lst);
		free(lst);
		free_tori(ori);
		exit(exit_code);
	}
}

int	convert_code(int num)
{
	if (num == 255 || num == 256 || num == -1)
		return (1);
	return (num);
}

void	free_tori(t_ori *ori)
{
	if (ori->cmds)
		free_tcmd(ori->cmds);
	if (ori->parsee)
		free_pars_ls(ori->parsee);
	if (ori->request)
		free(ori->request);
	ori->cmds = NULL;
	ori->nb_heredoc = 0;
	ori->parsee = NULL;
	ori->request = NULL;
}
