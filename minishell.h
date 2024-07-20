/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:28:08 by chanypar          #+#    #+#             */
/*   Updated: 2024/07/20 23:21:18 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TEMP ".temp_heredoc.txt"

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <unistd.h>

typedef enum s_type_redir
{
    REDIR_IN_S,
    REDIR_OUT_S,
    HEREDOC,
    REDIR_OUT_D,
}   e_type_redir;

typedef struct s_redir
{
    e_type_redir    type;
    char            *filename;
    int             fd;
    FILE*           f;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            *command;
    char            **arguments;
    t_redir         *redirections;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_envp
{
	char			*name;
	char			*value;

	struct s_envp	*next;
	struct s_envp	*prev;
	int				unset;
}					t_envp;

typedef struct s_pipe
{
	int				num_pipes;
	int				**fds;
	int				*pids;
}					t_pipe;

// typedef struct s_ori
// {
// 	t_cmds			*cmds;
// 	t_envp			*envs;
// 	char			*request;
// }					t_ori;

int     parsing_command(t_cmd *c, t_envp **lst);
int     check_exec_status(char *command, int status, char *check, int o_status);
int     oper_redir_in(t_cmd *c, int stdin_save);
int     oper_redir_out(t_cmd *c, int stdout_save);
int     oper_heredoc_in(t_cmd *c, int stdin_save, t_envp **lst);
int	    oper_redir_app(t_cmd *c, int stdout_save);
int	    redirec_main(t_cmd	*command, t_envp **lst);
int	    parsing_command(t_cmd *c, t_envp **lst);
int	    execute_parsing(t_cmd *c, int std_s[], t_envp **lst);
int	    close_file(t_redir *redirections);
int	    reset_stdin_out(int copy_stdin_out[]);
int     pipe_main(t_cmd	**commands, t_envp **list);
int     count_pipes(t_cmd **commands);

extern int			g_exit_code;

#endif