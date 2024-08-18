NAME = minishell
CC = cc
CFLAG = -MMD -g3 -Wall -Wextra -Werror
LDFLAG = -lreadline -lncurses
LIBFTDIR = ./libft

FILES = parsing/env.c parsing/expands.c parsing/expands_utils.c parsing/utils.c parsing/lexing.c\
	parsing/split_request.c parsing/syntax.c parsing/post_parsing.c parsing/automate.c parsing/all_toge.c\
	builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_export.c\
	builtins/ft_pwd.c builtins/ft_unset.c builtins/ft_exit.c builtins/built_utils.c\
	redir/redirec_main.c redir/redir_utils.c redir/redir_utils2.c redir/expand_hd.c\
	main.c main_utils.c iexec/helpers.c  \
	pipe/pipe_utils.c pipe/pipe_main.c parsing/pro_pars.c iexec/iexecori.c iexec/ft_heredoc.c \
	iexec/ft_redir.c  iexec/iexec_utils1.c iexec/iexec_utils2.c iexec/iexec_utils3.c \
	iexec/signals.c   parsing/expands_1.c  parsing/propars_1.c parsing/utils2.c \
	parsing/utils3.c

SRCS_DIR := ./src
OBJS_DIR := ./poubelle

SRCS := $(addprefix $(SRCS_DIR)/, $(FILES)) 
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))
DEPS := $(OBJS:.o=.d)

HEADERS := ./include

# COLOR #
GREEN	:= \033[38;5;76m
RED		:= \033[38;5;160m
YELLOW	:= \033[38;5;226m
ORANGE	:= \033[38;5;202m
PURPLE	:= \033[38;5;213m
LBLUE	:= \033[38;5;51m
BLUE	:= \033[38;5;117m
INDI	:= \033[38;5;99m
RESET	:= \033[00m

# List of subdirectories in which to create object files
OBJ_SUBDIRS := $(sort $(dir $(OBJS)))

all : $(NAME)

$(NAME): $(OBJS)
	@make --silent -C ${LIBFTDIR}
	@$(CC) $(CFLAG) -I$(HEADERS) -o $@ $(OBJS) -L$(LIBFTDIR) -lft $(LDFLAG)
	@printf "$(RED)"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠹⢿⡿⠏⢻⢿⠉⣿⣰⡟⠈⠘⠀⠀⠀⠀⠀⠰⠁⠘⠀⠘⠀⣿⠏⠀⢸⠃⢁⡛⣼⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣯⣿⣿⣿⠿⣿⣿⣿⡽⠝⢿⣿⡄⠘⠃⠀⠟⠀⠀⠘⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠁⠀⠀⢁⡟⢃⠁⣻⣿⡿⣿⡏⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣧⡀⢻⣿⠇⠀⠈⠃⠇⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⢧⠙⢐⣿⣿⡿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⢏⠔⣹"
	@echo "⣿⣿⣿⣿⣿⡟⢿⡈⠑⡀⠂⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⣼⡟⡻⣷⣿⣿⣿⣿⣿⣿⣿⣿⡿⠣⢁⣮⡟"
	@echo "⣿⣿⣿⣿⣿⣦⡕⢷⢁⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢀⣿⢋⣾⣿⣿⣿⣿⣿⣿⡟⡀⠁⣶⠋⠀"
	@echo "⣿⣿⣟⢿⢿⣷⣕⣌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠁⣽⢯⣾⣿⣿⣿⡟⡴⠰⠗⠸⠁⠀⠀"
	@echo "⣏⠿⣿⡧⡀⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⢀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣬⣿⣿⣿⣿⢸⡇⡻⡁⠀⠀⠀⠀"
	@echo "⣿⢧⠈⣿⠘⠀⠀⠀⠀⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠀⡠⠂⠀⠀⠀⠀⠀⠀⠁⠐⠀⠀⡀⠤⠀⠀⠀⠀⠀⠀⠉⠈⠀⠁⢀⠤⠀⠀⠘⠏⢸⢏⣽⣿⣞⢡⠃⡀⠀⠄⠀⠀"
	@echo "⣿⡆⠀⠈⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠄⡤⠆⠀⠀⠀⢠⠀⢀⠂⠀⠀⠀⠀⠀⠀⢀⠀⠀⢀⡀⠀⠀⠄⠀⠀⠀⠀⠀⢠⣄⠀⠰⢫⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣮⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠜⠀⠀⠀⠀⠂⠂⠀⠀⠀⠀⠀⠀⠂⠀⠐⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠋⠀⠀⠀⢰⢷⠿⡿⡄⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠉⠉⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⡇⠠⢠⠋⠀⠀⠀⠀⠆⠀⢠⣴⣾⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠠⠈⡄⠀⠘⢈⢰⢃⡌⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣷⣢⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡠⢠⢃⣀⡾⠀⠀⠀⠀⠃⢀⣴⣿⣿⡿⠛⠀⢀⣀⣠⢤⡄⢀⣀⣀⠀⠀⠄⠀⠀⢀⠀⠀⠚⠀⠀⠀⠻⡀⠸⠘⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⡥⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠁⠇⠀⡂⠁⠀⠀⠀⠀⠁⠀⣿⡿⠟⠉⢀⡴⢚⣋⡩⠅⡀⡀⡀⠉⠉⠙⠀⠀⡀⠑⠄⠀⠀⠀⠀⢠⡄⣠⡇⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀"
	@echo "⠤⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠈⠢⠀⠂⠁⠀⠀⠀⠠⢄⠀⠀⠋⠀⠀⣠⣤⣶⣿⣮⣭⣗⣺⠶⠶⠦⣤⣄⡂⠀⠈⠤⠀⠂⠀⠀⡫⡀⠈⠁⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣤⣍⠑⠀⠀⠀⠀⠀⠀⠀⠤⣤⠐⠀⠀⠁⠀⠀⠀⡀⠔⡈⠐⢐⠂⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⡟⠻⢫⠔⣤⡉⠻⣄⢄⠀⠀⠀⠁⠐⠀⠀⠀⡈⠀⠀⢀⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣟⣃⣀⠀⠀⠀⠀⠀⠀⢰⠔⠊⠋⠀⠀⠀⢀⢠⡠⢄⣨⣵⡴⠪⠴⡾⠿⠛⢿⣿⣟⡛⡛⠛⡭⠛⢛⡷⢦⡁⠈⠙⡢⡈⠑⢄⠠⠀⡀⠐⡀⠀⠀⠀⠀⠀⠸⣧⡱⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣷⣶⣁⣤⡠⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣴⣤⣈⣙⣛⣁⣀⡁⠁⣤⣶⣾⣿⣿⣿⡿⠆⠂⠀⠀⠀⠈⠑⠪⠳⣄⠈⠂⣀⠈⠳⣔⠔⠀⠐⠀⠀⠀⠀⠁⠀⠹⣷⣷⠆⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣯⡤⠤⠀⠀⠀⠀⢀⣀⠤⣄⣤⡸⣿⡿⡏⢉⠉⠉⠉⢀⣸⣿⣿⠿⠟⠛⢁⣄⡀⠠⡠⡀⠀⠀⠀⢠⠐⠢⡑⡄⡈⠡⡀⠈⢎⠁⠀⢣⠐⡈⠀⠀⠀⠀⠘⡏⠀⠀⠀⠀⠀⠠⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣶⡀⠀⠀⣤⣶⣿⠟⠁⠀⠰⡑⠌⠁⠀⠒⠾⢿⡿⠛⣁⠌⣠⣤⣜⢿⣿⡆⠊⢪⣦⠑⠄⠀⠁⠈⠈⠪⣠⠂⡈⢀⠈⢢⢦⡡⢣⠡⠀⠀⣿⡄⢀⠡⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣋⣀⠀⢐⡻⡇⠰⠐⣠⣧⠡⠀⠄⢀⢀⠔⠁⠀⣠⣵⣦⡻⣿⣿⡦⠙⠮⢂⡁⠈⠀⠀⠀⠀⠀⠀⠢⠈⠩⠢⣀⠡⡀⢣⠀⠀⢂⠄⠀⠘⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣶⣿⣷⣌⠉⠰⣰⣱⣿⡏⠀⣾⣾⠟⠁⠀⣠⣄⢿⣿⣿⣷⠈⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⢮⣦⡑⠠⢣⠀⢀⠈⠀⠀⠠⠇⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠅⣿⣿⡇⠰⣿⠁⠀⢄⡸⣿⣿⣦⠙⠃⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡄⠀⠑⢄⢻⣯⡀⠈⢆⡀⠀⠀⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠿⣿⠇⠁⠃⠀⠀⢸⣷⡝⠟⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⣀⣄⠁⠈⣥⡀⠐⠠⠙⣿⡀⠀⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠛⢈⠄⡀⠀⠀⢡⡻⠓⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠠⡀⢔⣶⣿⣶⠊⢻⠁⠀⣤⣙⢢⠀⠀⠘⢯⡄⠈⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠢⠈⠀⠀⠀⠡⠂⠀⣀⡀⡀⠀⠀⠀⠢⡀⡀⠀⢄⢀⣼⣿⣿⣏⠀⢀⠀⢸⣭⡙⠷⡁⠀⠀⠀⢻⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠈⠢⠀⠀⠀⠁⠈⠁⠀⠀⠀⠈⠀⠨⣮⣶⣤⣿⣿⣿⣿⡷⠀⠀⢲⣭⣛⢿⡀⠗⠀⠀⠀⠐⡁⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⢠⢠⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⠈⠐⠠⠀⠀⠀⠀⠀⠀⠀⠀⢢⣿⣿⣿⣿⣿⣿⠙⠁⠀⠀⣯⠻⣿⣷⡡⡀⠀⠀⢀⢁⠀⠀⠀⢈⠀⠀⠀⠀⠀⠀⠀⠀⡆⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠓⢄⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⡿⠛⢋⠂⢀⣄⠺⣿⣷⡘⣟⠃⠀⡀⠀⠠⠀⢀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⡇⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣿⣿⣦⡀⠡⠀⢀⠀⠀⠐⢄⢄⡉⠁⠅⢀⣠⡐⢿⣿⣦⠈⢿⠇⢀⣀⢢⠁⠀⠄⠀⠀⠀⠀⠘⡇⡀⠀⠀⠀⠀⠀⢰⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⢁⠙⣻⡿⠛⢛⣶⣄⠀⠀⡔⢄⠀⠳⣄⢆⡳⣤⡙⢿⣦⢙⠛⠈⢀⣴⣿⠿⠃⠀⠀⠀⠀⠂⠀⠀⢠⡇⠅⠀⠀⠀⠀⠀⡄⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣵⣿⣿⣿⣿⣿⣿⠃⠀⡌⡸⠟⠑⠀⢈⠁⠀⡰⢁⠈⢄⠃⢢⡈⠳⠝⢶⡩⠔⠉⢉⣤⣿⠿⠛⠁⠀⠀⣀⣴⡆⠨⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠃⠂⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⢰⠏⣽⣿⣿⣿⡿⡡⠀⠀⠀⠆⠃⠀⠀⢂⠀⠀⠃⠀⠀⠠⡙⢄⠝⢆⠀⠀⠁⢀⣴⡿⠟⠁⠀⠀⣀⣤⣼⣿⡿⠿⠀⠀⠀⠀⢀⢡⡌⠀⠀⠀⠀⠄⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⡸⠏⣿⠋⢁⠄⠃⠀⠈⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠁⠀⠀⠉⠁⠀⠀⠀⣀⣼⣿⠿⠻⠉⠃⠀⠀⠀⠀⠀⠈⣡⠀⠀⠀⠀⡸⠁⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠂⠀⠀⠀⡀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣿⢻⠋⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡏⠀⠀⠀⠀⠁⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⡟⡾⠟⡀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⡀⠈⠢⣀⠀⠈⠀⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠈⠻⢯⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⡠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⣿⣿⣿⣿⣿⣿⡵⡀⠞⡁⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠄⡀⠠⢀⠁⠠⢀⠀⠁⠂⠄⢂⠤⢀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠂⢄⡀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀"

# Create object directories
$(OBJS_DIR) $(OBJ_SUBDIRS):
	@mkdir -p $@

-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_SUBDIRS)
	@printf "$(LBLUE)[Compilation]$(RESET) In progress... $(GREEN)$<" && \
	$(CC) $(CFLAG) -I$(HEADERS) -c $< -o $@ && \
	printf "\r$(LBLUE)[Compilation]$(RESET) Completed   ... $(GREEN)$<" && \
	printf " $(LBLUE)[$(RESET)$(CC)$(LBLUE)/]$(RESET)\n"

clean :
	@echo "\033[0;31m\nObjects files will be destroyed[...]\n"
	@make --silent clean -C ${LIBFTDIR}
	@rm -rf $(OBJS_DIR)
	@echo "\033[0;32m\nDONE!\n"

fclean : clean
	@echo "\033[0;31m\nExecutes files will be destroyed[...]\n"
	@rm -f $(LIBFTDIR)/libft.a
	@rm -f $(NAME) 
	@echo "\033[0;32m\nDONE!\n"

re : fclean all

.PHONY: all clean fclean re