/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:07:25 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/20 21:17:52 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	init_state(t_cmds *token)
{
	if (!token)
		return (true);
	if (token->code_id == WORD)
		return (word_state(token->next));
	else if (token->code_id != WORD && token->code_id != PIPE_N)
		return (redir_state(token->next));
	else
		return (printf("syntax error near unexpected token '|'") , false);
}

bool	word_state(t_cmds *token)
{
	if (!token)
		return (true);
	if (token->code_id == WORD)
		return (word_state(token->next));
	if (token->code_id != WORD && token->code_id != PIPE_N)
		return (redir_state(token->next));
	else
		return (pipe_state(token->next));
}

bool	redir_state(t_cmds *token)
{
	if (!token)
		return (false);
	if (token->code_id == WORD)
		return (word_state(token->next));
	else
    
		return (false);
}

bool	pipe_state(t_cmds *token)
{
	if (!token)
		return (false);
	if (token->code_id == WORD)
		return (word_state(token->next));
	if (token->code_id != WORD && token->code_id != PIPE_N)
		return (redir_state(token->next));
	else
		return (false);
}