/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/07/29 16:51:05 by ihibti           ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_cmds		**ret;
	t_pars		**parsee;
	t_envp		**lst;
	t_status	*status;
	char		*string;
	t_pars		*test;
	t_redir		*redir;
	int			i;

	set_param(ac, av, &status);
	lst = lst_env(env);
	while (1)
	{
		string = ft_readline(status);
		ret = split_token(string);
		free_ret_nul(string);
		code_attr(ret);
		expanding(ret, lst);
		ret = pptreatment(ret);
		parsee = parser(ret);
		test = *parsee;
		while (test)
		{
			i = 0;
			printf("args:\n");
			while (test->arguments[i])
				printf("%s\n", test->arguments[i++]);
			redir = test->redirections;
			printf("redir\n");
			while (redir)
			{
				printf("%s\n", redir->filename);
				redir = redir->next;
			}
			test = test->next;
		}
		// if (*ret)
		// 	(*ret)->status = status;
		// if (ret && *(ret))
		// 	g_exit_code = convert_code(pipe_main(ret, lst, env));
		// ft_free_all(ret, lst, status, 0);
		// check_exit_code(status, g_exit_code, lst);
	}
	return (0);
}
