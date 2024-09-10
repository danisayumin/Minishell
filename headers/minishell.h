/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:16:33 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/10 19:17:331 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>

# define PROMPT "minishell$ "

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}	t_io_node;

typedef enum e_node_type
{
	N_CMD
}	t_node_type;

typedef struct s_node
{
	t_node_type			type;
	t_io_node			*io_list;
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}	t_parse_err_type;

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*str;
}	t_parse_err;

typedef struct s_minishell
{
	char		*line;
	t_token		*tokens;
	t_token		*curr_token;
	t_node		*ast;
	int			exit_s;
	bool		signint_child;
	t_parse_err	parse_err;
	int			stdin;
	int			stdout;
	char		**environ;
	t_env		*envlst;
	bool		heredoc_sigint;
	struct termios	original_term;
}	t_minishell;

extern t_minishell    g_minishell;

#endif