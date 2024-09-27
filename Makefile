NAME		:= minishell

LIBFT		:= ./libft/libft.a
LIBFT_PATH	:= "./libft"

CC			:= cc

CFLAGS		:= -Wall -Wextra -Werror 

BUILTINS	:=	builtins/echo.c \
				builtins/env_utils.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/pwd.c \
				builtins/cd.c \
				builtins/unset.c \
				builtins/export.c

CLEANING	:=	clear.c

EXEC		:=	exec/exec_redirect.c \
				exec/exec_utils.c \
				exec/exec.c \
				exec/exist_check.c \
				exec/ft_exec_simple_cmd.c \
				exec/ft_get_path.c \
				exec/exec_builtins.c \
				exec/ft_init_tree.c

EXPANDER	:=	expander/ft_asterisker.c \
				expander/ft_expand_utils.c \
				expander/ft_expand.c \
				expander/ft_expander_split.c \
				expander/ft_globber_utils.c \
				expander/ft_globber.c \
				expander/ft_strip_quotes.c \
				expander/ft_heredoc_expander.c

PARSING		:=	parser/parser_clear.c \
				parser/parser_error.c \
				parser/parser_helpers.c \
				parser/parser_nodes.c \
				parser/parser_utils.c \
				parser/parser.c

TOKENIZING	:=	tokens/tokenizer_appenders.c \
				tokens/tokenizer_handler.c \
				tokens/tokenizer_lst.c \
				tokens/tokenizer_utils.c \
				tokens/tokenizer.c

SRCS		:=	$(PARSING)\
				$(TOKENIZING)\
				$(BUILTINS)\
				$(CLEANING)\
				$(EXEC)\
				$(EXPANDER)\
				main.c signals.c general_utils.c

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH:=	readline #mudar p linux

%.o: %.c
	$(CC) $(CFLAGS)-Iheaders -I$(READLINE_PATH)  -c $< -o $@ 

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) bonus

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(LIBFT) -L$(READLINE_PATH) -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re