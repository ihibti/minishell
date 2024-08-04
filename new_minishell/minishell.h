/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:28:08 by chanypar          #+#    #+#             */
/*   Updated: 2024/08/04 20:18:45 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define TEMP ".temp_heredoc.txt"
# define WORD 9
# define PIPE_N 10
# define REDIR_IN 11
# define REDIR_OUT 12
# define HEREDOC_IN 13
# define REDIR_APP 14
# define SIN_QUOTE 20
# define DOUB_QUOTE 21
# define TOKEN_EX_STT 22

typedef struct s_cmds
{
	int				flag;
	int				code_id;
	char			*name;
	struct s_cmds	*prev;
	struct s_cmds	*next;
	struct s_file	**file;
	char			**env;
}					t_cmds;

typedef struct s_file
{
	int				fd;
	FILE			*f;
	char			*file_name;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct s_exptr
{
	struct s_cmds	**cmds;
	struct s_envp	**env;
	int				num;
}					t_exptr;

typedef enum s_type_redir
{
	REDIR_IN_S,
	REDIR_OUT_S,
	HEREDOC,
	REDIR_OUT_D,
}		t_type_redir;

typedef struct s_redir
{
	t_type_redir				type;
	char						*filename;
	int							fd;
	FILE*						f;
	struct s_redir				*next;
}	t_redir;

typedef struct s_pars
{
	char					*command;
	char					**arguments;
	t_redir					*redirections;
	struct s_pars			*next;
}	t_pars;

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

typedef struct s_ori
{
	t_cmds			**cmds;
	t_envp			**envs;
	t_pars			**parsee;
	char			*request;
}					t_ori;

int					keep_pars(t_pars *new, t_cmds *cmd);
t_pars				**parser(t_cmds **cmds);
int					add_last_redir(t_redir *new, t_pars *pars);
void				add_last_par(t_pars **pars, t_pars *new);
int					add_arg(t_pars *pars, char *new);
bool				init_state(t_cmds *token);
bool				word_state(t_cmds *token);
bool				redir_state(t_cmds *token);
bool				pipe_state(t_cmds *token);
t_cmds				*ft_new_tcmd(char *str, int code);
int					code_attr(t_cmds **cmds);
int					ft_occur(char *str, char c);
char				*ft_strlimdup(char *str, int lim);
t_cmds				**ft_last_tcmd(char *str, int code, t_cmds **list_cmd);
int					non_print(char *str);
t_cmds				**split_token(char *request);
int					ft_pos_c(char *str, char c);
char				*end_quote(char *str, char c);
int					is_not_word(char *str);
int					syn_err(char *str);
int					open_quote(char *str);
int					code_lex(char *str);
int					is_not_word(char *str);
int					meta_type(char *str);
int					type_quote(char *str);
int					ft_tablen(char **env);
int					is_token(char *str);
int					tok_acc(char *str);
t_envp				**add_envplast(t_envp **ret, char *str);
t_envp				**add_envplast_null(t_envp **ret, char *str);
void				*free_envp(t_envp **lst);
t_envp				**lst_env(char **env);
int					is_lim_exp(char c);
t_envp				*env_match(char *str, t_envp **lst);
int					expanding(t_cmds **cmds, t_envp **lst);
int					nb_expand(t_cmds *cmd);
int					exp_exception(char *str);
int					replace_exp(t_cmds *cmd, t_envp **lst);
char				*new_expanded(char *str, char *ptr, t_envp *match);
char				*nomatch(char *ptr, char *str);
void				reset_sp_tok(int *i, int *j);
int					skip_spcaes(int *i, char *request);
int					n_end_quote(char *str, int i, int j);
int					ft_isspace(char c);
int					go_last_lex(char *str, int i, int j);
void				init_0(int *i, int *j);
int					interpret(char *str, char *ptr);
void				free_tcmd(t_cmds **cmds);
t_cmds				**pptreatment(t_cmds **cmds);
int					replace_quote(t_cmds *cmds);
int					update_env(t_envp **lst, char *key, char *n_value);
int					ft_cd(t_pars *pars, t_envp **lst);
int					ft_echo(t_pars *cmd);
int					ft_env(t_envp **lst);
int					ft_exit(t_pars *cmd);
int					ft_export(t_pars *pars, t_envp **env);
int					ft_pwd(void);
int					ft_unset(t_envp **lst, t_pars *pars);
int					ft_env(t_envp **lst);
void				check_exit_code(t_pars **commands,
						int exit_code, t_envp **lst, t_ori *ori);
int					convert_code(int num);
int					ch_err(int num, int cpy_stdin_out[]);
int					reset_stdin_out(int copy_stdin_out[]);
char				*expanding_hd(char *str, t_envp **envp);
char				*free_ret_nul(char *str);
void				cp_exp_beg(char **str, char **ret, int *j);
void				init_1(int *i, int *j, t_cmds ***ret);
char				**freee_error(char **tab);
int					free_ori(t_ori *ori);
void				free_pars_ls(t_pars **parsee);
char				*rep_ex_sig_hd(char *str, char *ptr);
char				*rep_ex_sig(char *str, char *ptr);
int					all_toge(t_ori *ori);

int					parsing_command(t_pars *c, t_envp **lst);
int					check_exec_status(char *command,
						int status, char *check, int o_status);
int					oper_redir_in(t_pars *c, int stdin_save);
int					oper_redir_out(t_pars *c, int stdout_save);
int					oper_heredoc_in(t_pars *c, int stdin_save, t_envp **lst);
int					read_heredoc(char *end_str, char *flag, t_envp **lst);
int					exec_heredoc(int flag);
int					oper_redir_app(t_pars *c, int stdout_save);
int					redirec_main(t_pars	*command, t_envp **lst);
int					parsing_command(t_pars *c, t_envp **lst);
int					execute_parsing(t_pars *c, int std_s[], t_envp **lst);
int					close_file(t_redir *redirections);
int					reset_stdin_out(int copy_stdin_out[]);
int					pipe_main(t_pars	**commands, t_envp **list);
int					count_pipes(t_pars **commands);
void				free_tori(t_ori *ori);

extern int			g_exit_code;

#endif