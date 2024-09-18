NAME		:= minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra

# BUILTINS	:=	builtins/cd.c \
# 				builtins/echo.c \
# 				builtins/env_utils.c \
# 				builtins/env.c \
# 				builtins/exit.c \
# 				builtins/export.c \
# 				builtins/pwd.c \
# 				builtins/unset.c

CLEANING	:=	clear.c

# EXEC		:=	exec/error_msg.c \
# 				exec/exec_builtin.c \
# 				exec/exec_redirect.c \
# 				exec/exec_utils.c \
# 				exec/exec.c \
# 				exec/exist_check.c \
# 				exec/ft_exec_simple_cmd.c \
# 				exec/ft_get_path.c \
# 				exec/init_tree.c

# EXPANDER	:=	expander/ft_asterisker.c \
# 				expander/ft_clean_empty_strs.c \
# 				expander/ft_expand_utils.c \
# 				expander/ft_expand.c \
# 				expander/ft_expander_split.c \
# 				expander/ft_globber_utils.c \
# 				expander/ft_globber.c \
# 				expander/ft_strip_quotes.c \
# 				expander/heredoc_expander.c

PARSING		:=	parser/parser_clear.c \
				parser/parser_err.c \
				parser/parser_helpers.c \
				parser/parser_nodes.c \
				parser/parser_utils.c \
				parser/parser.c

TOKENIZING	:=	tokens/tokenizer_appenders.c \
				tokens/tokenizer_handlers.c \
				tokens/tokenizer_lst.c \
				tokens/tokenizer_utils.c \
				tokens/tokenizer.c

SRCS		:=	$(PARSING)\
				$(TOKENIZING)\
				$(BUILTINS)\
				$(CLEANING)\
				$(EXEC)\
				$(EXPANDER)\
				main.c signals.c

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH:=	/goinfre/homebrew/opt/readline #mudar p linux

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE_PATH)/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re