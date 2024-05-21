/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihibti <ihibti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:20:33 by ihibti            #+#    #+#             */
/*   Updated: 2024/05/20 20:00:16 by ihibti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	int				code_id;
	char			*name;
	struct s_cmds	*prev;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_envp
{
	char			*name;
	char			*value;
	// Tableau de str contenant le nom et la valeur de chaque variable d'environnement
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;

typedef struct s_ori
{
	t_cmds			*cmds;
	t_envp			*envs;
	char			*request;
}					t_ori;

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
t_envp				**add_envplast(t_envp **ret, char *str);
void				*free_envp(t_envp **lst);
t_envp				**lst_env(char **env);
int					is_lim_exp(char c);
t_envp				*env_match(char *str, t_envp **lst);
int					expanding(t_cmds **cmds, t_envp **lst);
int					nb_expand(t_cmds *cmd);
int					exp_exception(char *str);
int					replace_exp(t_cmds *cmd, t_envp **lst);
char				*new_expanded(char *str, char *ptr, int i, t_envp *match);
char				*nomatch(char *ptr, char *str);
#endif
