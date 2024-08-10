/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:38:35 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/10 18:17:52 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	check_file_name(char *name, t_pars *cmd)
// {
// 	t_file	*file;

// 	file = (*(*ret)->file);
// 	while (file)
// 	{
// 		if (ft_strcmp(name, file->file_name) == 0)
// 			return (1);
// 		file = file->prev;
// 	}
// 	return (0);
// }

// void	execute(t_pars *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd && cmd->redirections
// 			&& (cmd->redirections->type == REDIR_IN_S
// 			|| cmd->redirections->type == REDIR_OUT_S))
// 	{
// 		while (cmd->redirections && cmd->arguments[i])
// 		{
// 			if (check_file_name(cmd->arguments[i], cmd))
// 				i++;
// 			cmd->redirections = cmd->redirections->next;
// 		}
// 		if (!cmd)
// 			break ;
// 		if (cmd && cmd->code_id == 9 && i)
// 			printf(" ");
// 		printf("%s", cmd->name);
// 		cmd = cmd->next;
// 		i = 1;
// 	}
// }
// int	check_option(t_pars *cmd)
// {
// 	t_pars	*temp;
// 	int		i;

// 	i = 0;
// 	temp = cmd;
// 	while (temp->arguments[i])
// 	{
// 		if (!ft_strcmp(temp->arguments[i++], "-n"))
// 			return (1);
// 	}
// 	return (0);
// }

int	ft_echo(t_ori *ori, t_pars *pars)
{
	int	flag;
	int	i;

	if (!pars)
		return (1);
	i = 1;
	if (pars->arguments && pars->arguments[1] && !ft_strncmp(pars->arguments[1],
			"-n",2))
	{
		flag = 0;
		i++;
	}
	else
		flag = 1;
	while (pars && pars->arguments && pars->arguments[i])
	{
		ft_putstr_fd(pars->arguments[i], ori->fraude);
		if (pars->arguments[i] && pars->arguments[i + 1])
			ft_putstr_fd(" ", ori->fraude);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", ori->fraude);
	return (0);
}
