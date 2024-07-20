#include "../../minishell.h"

bool init_state(t_cmds *token)
{
    if (!token)
        return (true);
    if (token->code_id == WORD)
        return (word_state(token->next));
    else if (token->code_id != WORD && token->code_id != PIPE_N)
        return (redir_state(token->next));
    else
        return (false);    
}

bool word_state(t_cmds *token)
{
    if (!token)
        return (true);
    if (token->code_id == WORD)
        return (word_state(token->next));
    if (token->code_id != WORD && token->code_id != PIPE_N)
        return (redir_state(token->next));
    if (token->code_id == PIPE_N)
        return (pipe_state(token->next));   
}

bool redir_state(t_cmds *token)
{
    if (!token)
        return (false);
    if (token->code_id == WORD)
        return (word_state(token->next));
    else
        return (false);  
}

bool pipe_state(t_cmds *token)
{
    if (!token)
        return (false);
    if (token->code_id == WORD)
        return (word_state(token->next));
    if (token->code_id != WORD && token->code_id != PIPE_N)
        return (redir_state(token->next));
    else
        return (false); 
}

typedef enum s_type_redir {
    REDIR_IN_S,
    REDIR_OUT_S,
    REDIR_OUT_D,
    HEREDOC,
}   e_type_redir;

typedef struct s_redir {
    e_type_redir    type;
    char *filename;
    struct s_redir *next;
}   t_redir;

typedef struct s_cmd {
    char *command;
    char **arguments;
    t_redir *redirections;
    struct s_cmd *next;
}   t_cmd;

t_redir *new_redir(e_type_redir type, char *filename)
{
    t_redir *res;

    res = malloc(sizeof(t_redir));
    res->type = type;
    res->filename = filename;
    res->next = NULL;
    return (res);
}
