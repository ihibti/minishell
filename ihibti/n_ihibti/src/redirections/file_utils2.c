/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:18:17 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/15 18:04:50 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_new_tfile(t_file **file, char file_name[], int fd)
{
	t_file *new;
	static int	isfirst;

	new = malloc(sizeof(t_file));
	if (!new)
		return (-1);
	new->file_name = file_name;
	new->fd = fd;
	new->f = NULL;
	if (!isfirst)
		new->prev = NULL;
	else
		new->prev = *(file);
	if (!isfirst)
		(*file) = new;
	else
		(*file)->next = new;
	new->next = NULL;
	if (isfirst)
		(*file) = (*file)->next;
	isfirst++;
	return (0);
}

void	ft_del_tfile(t_file **file, int fd)
{
	t_file *current;

	current = *(file);
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

int	close_file(t_file **file)
{
	t_file	*current_file;

	current_file = *(file);
	while (current_file->fd)
	{
		if (current_file->f)
		{
			if (f_close2(current_file->fd, file, current_file->f) == -1)
				return (-1);
			if (!(ft_strcmp(current_file->file_name, TEMP)))
				remove(TEMP);
		}
		else
		{
			if (f_close(current_file->fd, file) == -1)
				return (-1);
		}
		if (!current_file->next)
			break ;
		current_file = current_file->next;
	}
	return (0);
}
