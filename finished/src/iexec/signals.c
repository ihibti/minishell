/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:04:57 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 17:10:04 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	rl_on_new_line();
	if (isatty(0))
		ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_child(int useless)
{
	(void)useless;
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler_here_doc(int useless)
{
	(void)useless;
	close(0);
	g_exit_code = -999;
}
