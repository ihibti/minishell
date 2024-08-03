/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/08/03 16:27:55 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_code = 0;

void	sigint_handler(int sig)
{
	char	*cwd;

	(void)sig;
	if (g_exit_code != -2)
		printf("\n%s", "MINI:");
	else
		printf("\n");
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

void	set_param(int ac, char **av, t_status **status)
{
	(void)ac;
	(void)av;
	*status = malloc(sizeof(t_status));
	if (!*status)
		exit(-1);
	(*status)->isexit = 0;
	using_history();
	g_exit_code = 0;
}

char	*ft_readline(t_status *status)
{
	char	*cpy;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	cpy = NULL;
	cpy = readline("MINI:");
	while (cpy && !*cpy)
	{
		free(cpy);
		cpy = readline("MINI:");
	}
	if (!cpy)
	{
		rl_clear_history();
		free(cpy);
		free(status);
		exit(0);
	}
	history(cpy);
	return (cpy);
}

int	all_toge(t_ori *ori)
{
	ori->cmds = split_token(ori->request);
	if (!ori->cmds)
		return (free_ori(ori), 1);
	if (!*(ori->cmds))
		return (free_tcmd(ori->cmds), 0);
	code_attr(ori->cmds);
	expanding(ori->cmds, ori->envs);
	if (!ori->cmds)
		return (free_ori(ori), 1);
	ori->cmds = pptreatment(ori->cmds);
	if (!*ori->cmds)
		return (free_tcmd(ori->cmds), ori->parsee = NULL, 0);
	if (!init_state(*(ori->cmds)))
	{
		free_tcmd(ori->cmds);
		ori->parsee = NULL;
		return (0);
	}
	ori->parsee = parser(ori->cmds);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_status	*status;
	t_ori		ori;
	int			i;

	set_param(ac, av, &status);
	ori.envs = lst_env(env);
	while (1)
	{
		ori.request = ft_readline(status);
		if (all_toge(&ori))
			return (free_ori(&ori), 1);
		if (ori.parsee)
		{
			g_exit_code = convert_code(pipe_main(ori.parsee, ori.envs));
			check_exit_code(ori.parsee, g_exit_code, ori.envs);
		}
	}
	return (0);
}
