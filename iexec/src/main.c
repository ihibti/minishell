/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/15 14:49:58 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_code = 0;

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

void	history(char *str)
{
	HIST_ENTRY	**his_list;
	int			i;
	char		*cpy;

	i = -1;
	cpy = ft_strdup(str);
	his_list = NULL;
	add_history(cpy);
	free(cpy);
	his_list = NULL;
	his_list = history_list();
	if (ft_strcmp(str, "history") == 0)
	{
		while (his_list[++i])
			printf("%d: %s\n", i + 1, his_list[i]->line);
	}
}

void	set_param(int ac, char **av)
{
	(void)ac;
	(void)av;
	using_history();
	g_exit_code = 0;
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

void	init_ori(t_ori *ori)
{
	ori->cmds = NULL;
	ori->cmds = NULL;
	ori->parsee = NULL;
	ori->request = NULL;
	ori->nb_heredoc = 0;
	ori->fraude = 1;
	ori->fraude_in = 0;
	ori->need_exit = 0;
}

// TODO : changer le brexit et les exit status

int	main(int ac, char **av, char **env)
{
	t_ori	ori;
	int		i;

	set_param(ac, av);
	init_ori(&ori);
	ori.envs = lst_env(env);
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
		{
			if (loop_here(&ori))
			{
				free_tori(&ori);
				continue ;
			}
			built_ex(&ori);
		}
		unlink_hd(&ori);
		free_tori(&ori);
		ori.nb_heredoc = 0;
	}
	return (0);
}
