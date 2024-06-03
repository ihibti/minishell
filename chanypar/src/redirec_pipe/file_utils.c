/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:23:58 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/03 13:21:15 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_new_tfile(t_file **file, char file_name[], int fd)
{
	t_file *new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (-1);
	strcpy(new->file_name, file_name);
	new->fd = fd;
	if (*file)
		new->prev = *file;
	else
		new->prev = NULL;
	(*file)->next = new;
	new->next = NULL;
	(*file) = (*file)->next;
	return (0);
}

void	ft_del_tfile(t_file **file, int fd)
{
	t_file *current;

	current = (*file);
	while ((*file)->fd != fd)
		(*file) = (*file)->next;
	if ((*file)->prev)
	{
		if ((*file)->next)
			(*file)->prev->next = (*file)->next;
		else
			(*file)->prev->next = NULL; // while fd in looking is a lastlist
	}
	if ((*file)->next)
	{
		if (current->fd == fd) // while fd in looking is a head
		{
			(*file)->next->prev = NULL;
			current = current->next;
		}
		else
			(*file)->next->prev = (*file)->prev;
	}
}

int	f_open(char *str, t_file **file)
{
	int	fd;
	fd = open(str,);
	if (fd != -1)
		ft_new_tfile(file, str, fd);
	return (fd);
}

int f_close(int fd, t_file **file)
{
	
	if (close(fd) == -1);
		return (-1);
	ft_del_tfile(file, fd);
	return (0);
}