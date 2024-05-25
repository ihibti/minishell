/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:32:27 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/25 09:03:52 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char shell_prompt[100];

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n%s", shell_prompt);
}

void	history(char *str)
{
	HIST_ENTRY **the_history_list;
	int i;
	
	
	add_history(str);
	the_history_list = history_list();
	i = -1;
    while (the_history_list[++i])
		printf("%d: %s\n", i + 1, the_history_list[i]->line);
}

int	main(int ac, char **av, char **env)
{
	t_cmds **ret;
	t_cmds *current;
	t_envp **lst;
	char	*cwd;
	char	*usr;

	(void)ac;
	(void)av;
	char *cpy;
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	cwd = getcwd(NULL, 1024);
	usr = getenv("USER");
	if (!cwd || !usr)
		return (-1);
	snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", usr, cwd);	
	while (1)
	{
		cpy = readline(shell_prompt);
		if (!cpy || ft_strcmp(cpy, "exit") == 0)
		{
			free(cwd);
			free(cpy);
			break ;
		}
		ret = split_token(cpy);
		history(cpy);
		free(cpy);
		code_attr(ret);
		if (!ret)
			return (printf("porblemooo\n"), 1);
		current = *ret;
		while (current)
		{
			printf("char :%s\n", current->name);
			printf("code : %d\n_________\n", current->code_id);
			current = current->next;
		}
		lst = lst_env(env);
		expanding(ret, lst);
		current = *ret;
		while (current)
		{	
			printf("char :%s\n", current->name);
			printf("code : %d\n_________\n", current->code_id);
			current = current->next;
		}
		free_envp(lst);
		free_tcmd(ret);
	}

	return (0);
}
