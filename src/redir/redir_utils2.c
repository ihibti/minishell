/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:15:00 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/29 20:20:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	close_file(t_redir *redirections)
{
	if (access(TEMP, F_OK), TEMP)
		unlink(TEMP);
	while (redirections)
	{
		if (redirections->f)
		{
			if (fclose(redirections->f) == -1)
				return (-1);
		}
		else
		{
			if (close(redirections->fd) == -1)
				return (-1);
		}
	}
	return (-1);
}

int	reset_stdin_out(int copy_stdin_out[])
{
	if (copy_stdin_out[0])
	{
		if (dup2(copy_stdin_out[0], STDIN_FILENO) == -1)
		{
			copy_stdin_out[0] = 0;
			return (-1);
		}
	}
	if (copy_stdin_out[1])
	{
		if (dup2(copy_stdin_out[1], STDOUT_FILENO) == -1)
		{
			copy_stdin_out[1] = 0;
			return (-1);
		}
	}
	return (0);
}

int	ch_err(int num, int cpy_stdin_out[])
{
	if (num == -1)
	{
		reset_stdin_out(cpy_stdin_out);
		return (-1);
	}
	return (num);
}
