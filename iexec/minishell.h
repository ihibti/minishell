/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:28:08 by chanypar          #+#    #+#             */
/*   Updated: 2024/08/16 16:13:32 by ihibti           ###   ########.fr       */
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
# define E_MALLOC "Error: malloc failed : "
# define E_ARGS "Error: too many arguments\n"
# define E_SYNTAX "syntax error near unexpected token "
# define E_HEREDOC "\nhere-document delimited by end-of-file wanted "
# define E_PIPE "Error: pipe failed\n"
# define E_REDIR "ambiguous redirect : "
# define E_EOF "unexpected EOF while looking for matching "
# define E_S_EOF "syntax error : unexpected EOF\n"
# define E_DIR_ERROR "error retrieving current directory: "
# define E_GETCWD_ERROR "getcwd: cannot access parent directories:"
# define E_EXIT "exit: "
# define E_EXIT_MANY "too many arguments\n"
# define E_EXIT_NUM "numeric argument required\n"
# define E_EXPORT "export: "
# define E_2 ": "
# define E_EXPORT_ID "not a valid identifier"
# define E_CD "cd: "
# define E_ENV "env: "
# define E_FORK "fork error\n"
# define E_OPEN "error opening file\n"
# define FRAUDE 77
# define LEGIT 44
# define HD "heredoc"

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
}					t_type_redir;

typedef struct s_redir
{
	t_type_redir	type;
	char			*filename;
	int				fd;
	FILE			*f;
	struct s_redir	*next;
}					t_redir;

typedef struct s_pars
{
	char			*command;
	char			**arguments;
	t_redir			*redirections;
	struct s_pars	*next;
}					t_pars;

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
	int				nb_heredoc;
	int				fraude;
	int				fraude_in;
	int				need_exit;

}					t_ori;

void				reset_syn(int *i, int *j);
void				advance(char *str, int *i);
t_redir				*new_redir(t_type_redir type, char *filename);
int					add_last_redir(t_redir *new, t_pars *pars);
int					cond_helper(char *str, int i);
char				*nomatch_hd(char *ptr, char *str);
char				*rep_ex_sig_hd(char *str, char *ptr);
int					exp_exception_hd(char *str);
int					nb_expand_hd(char *str);
char				*new_expanded_hd(char *str, char *ptr, t_envp *match);
void				set_signals(void);
void				exec_loop(t_ori *ori);
t_pars				*init_pipex(t_ori *ori, int *i, int *flag);
t_redir				*init_dodup(t_ori *ori, int i);
int					is_dir(char *cmd);
int					unlink_hd(t_ori *ori);
int					do_built(t_ori *ori, int soul, t_pars *current);
void				safe_close(int fd);
void				sigint_handler_here_doc(int useless);
void				sigint_handler_child(int useless);
void				close_fd(int fd, int i);
void				close_all_fd(int pipe_fd[2], int c_fd, int i,
						bool close_fd_0);
void				redir_out(int pipe_fd[2], int flag[4], t_redir *redir,
						t_ori *ori);
void				do_dup(int c_fd, int pipe_fd[2], int i, t_ori *ori);
int					ft_heredoc(t_redir *redir, char *modified, t_ori *ori);
int					loop_here(t_ori *ori);
int					wait_for_child(pid_t pid);
int					brexit(t_ori *ori, char *msg, int exitc);
int					pipex(t_ori *ori);
char				*pathfinder(char *cmd, char **path_t);
char				**env_trans(t_envp **lst);
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
int					ft_cd(t_ori *ori, t_pars *pars);
int					ft_echo(t_ori *ori, t_pars *pars);
int					ft_env(t_ori *ori, t_pars *pars);
int					ft_exit(t_ori *ori, t_pars *pars);
int					ft_export(t_ori *ori, t_pars *pars);
int					ft_pwd(t_ori *ori, t_pars *pars);
int					ft_unset(t_ori *ori, t_pars *pars);
int					ft_env(t_ori *ori, t_pars *pars);
void				check_exit_code(t_pars **commands, int exit_code,
						t_envp **lst, t_ori *ori);
int					convert_code(int num);
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
int					check_exec_status(char *command, int status, char *check,
						int o_status);
int					count_pipes(t_pars **commands);
void				free_tori(t_ori *ori);
void				built_ex(t_ori *ori);
void				*get_built_func(t_pars *current);

extern int			g_exit_code;

#endif