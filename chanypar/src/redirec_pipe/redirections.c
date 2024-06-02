/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:49:28 by chanypar          #+#    #+#             */
/*   Updated: 2024/06/02 20:25:05 by chanypar         ###   ########.fr       */
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
	dup2(fd, STDOUT_FILENO);
	execute_command(command, current->next, lst);
	dup2(stdout_save, STDOUT_FILENO);
	fclose(file);
}

int	operation_redir_out(t_cmds *current, t_cmds **ret, t_envp **lst)
{
	int		fd;
	int		command;
	int		stdin_save;
	char	*content;

	command = 0;
	command = builtins_checker(current);
	if (command == -1)
		return (-1);
	if (!current->next && (current->next->code_id >= 10
			&& current->next->code_id <= 14))
		return (-1);
	stdin_save = dup(0);
	fd = open(current->next->name, O_RDONLY);
	if (!fd)
		return (-1);
	content = read_file(fd);
	dup2(fd, 0);
	execute_command(command, current->next, lst);
	dup2(stdin_save, 0);
	close(fd);
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

