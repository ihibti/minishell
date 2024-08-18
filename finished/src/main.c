/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/17 13:28:05 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_code = 0;

void	history(char *str)
{
	char	*cpy;

	cpy = ft_strdup(str);
	add_history(cpy);
	free(cpy);
}

int	set_param(int ac, char **av, char **env)
{
	if (ac != 1)
		return (ft_putstr_fd("no arguments needed\n", 2), 1);
	(void)env;
	(void)av;
	g_exit_code = 0;
	return (0);
}

char	*ft_readline(t_ori *ori)
{
	char	*cpy;

	set_signals();
	cpy = NULL;
	cpy = readline("MINI:");
	while (cpy && !*cpy)
	{
		free(cpy);
		cpy = readline("MINI:");
	}
	if (!cpy)
	{
		free_ori(ori);
		rl_clear_history();
		exit(0);
	}
	history(cpy);
	return (cpy);
}

void	init_ori(t_ori *ori, char **env)
{
	ori->cmds = NULL;
	ori->cmds = NULL;
	ori->parsee = NULL;
	ori->request = NULL;
	ori->nb_heredoc = 0;
	ori->fraude = 1;
	ori->fraude_in = 0;
	ori->need_exit = 0;
	ori->envs = lst_env(env);
	if (!ori->envs)
		brexit(ori, E_MALLOC, 1);
}

// TODO : changer le brexit et les exit status

int	main(int ac, char **av, char **env)
{
	t_ori	ori;

	if (set_param(ac, av, env))
		return (0);
	init_ori(&ori, env);
	while (1)
	{
		ori.request = ft_readline(&ori);
		if (all_toge(&ori))
			return (free_ori(&ori), 1);
		if (!ori.parsee)
		{
			free_tori(&ori);
			continue ;
		}
		else
			exec_loop(&ori);
		unlink_hd(&ori);
		free_tori(&ori);
		ori.nb_heredoc = 0;
	}
	return (0);
}
