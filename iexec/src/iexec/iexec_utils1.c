/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iexec_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:26:07 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 16:30:30 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	safe_close(int fd)
{
	if (fd > 1)
		close(fd);
}

void	close_fd(int fd, int i)
{
	if (fd > -1)
		close(fd);
}

void	close_all_fd(int pipe_fd[2], int c_fd, int i, bool close_fd_0)
{
	if (close_fd_0 == true)
		close(pipe_fd[0]);
	close_fd(c_fd, i);
	close(pipe_fd[1]);
}

// TODO : changer pour avoir en parametres le __msg___

int	brexit(t_ori *ori, char *msg, int exitc)
{
	if (msg)
		printf("%s\n", msg);
	free_ori(ori);
	exit(exitc);
}

int	nb_pipes(t_pars *current)
{
	int	i;

	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
