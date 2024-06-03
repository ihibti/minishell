/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:49:28 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/03 14:51:26 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	operation_redir_in(t_cmds *current, t_cmds **ret, t_envp **lst)
{
	FILE	*file;
	int		fd;
	int		command;
	int		stdout_save;

	command = 0;
	command = builtins_checker(current);
	if (command == -1)
		return (-1);
	if (!current->next && (current->next->code_id >= 10
			&& current->next->code_id <= 14))
		return (-1);
	stdout_save = dup(STDOUT_FILENO);
	file = fopen(current->next->name, "wr");
	if (!file)
		return (-1);
	fd = fileno(file);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	execute_command(command, current->prev, lst);
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
		return (-1);
	fclose(file);
}

int	operation_redir_out(t_cmds *current, t_cmds **ret, t_envp **lst)
{
	int		fd;
	int		command;
	int		stdin_save;
	// char	*content;

	command = 0;
	command = builtins_checker(current);
	if (command == -1)
		return (-1);
	if (!current->next && (current->next->code_id >= 10
			&& current->next->code_id <= 14))
		return (-1);
	stdin_save = dup(STDIN_FILENO);
	fd = open(current->next->name, O_RDONLY);
	if (!fd)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	// content = read_file(STDIN_FILENO); 
	free(current->next->name);
	current->next->name = content;
	execute_command(command, current->prev, lst);
	if (dup2(stdin_save, STDIN_FILENO) == -1)
		return (-1);
}

int	redirec_main(t_cmds **ret, t_file **file, t_envp **lst)
{
	t_cmds	*current;

	current = find_redirec(ret);
	if (!current)
		return (-1);
	if (current->code_id == 11) // "<"
		operation_redir_in(current, ret, lst);
	else if (current->code_id == 12) // ">"
		operation_redir_out(current, ret, lst);
	else if (current->code_id == 13) // "<<"
		operation_heredoc_in(current, ret);
	else if (current->code_id == 14) // ">>"
		operation_reduc_app(current, ret);
	return (0);
}

