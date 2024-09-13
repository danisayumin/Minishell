/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:00:59 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/13 11:41:23 by dsayumi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.environ = env;
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);
	tcgetattr(STDIN_FILENO, &g_minishell.original_term);
}

static void	ft_sigint_handler(int num) // ver se nao ada bo
{
	(void)num;
	if (g_minishell.signint_child)
	{
		ft_putstr_fd("\n", 1);
		g_minishell.signint_child = false;
		g_minishell.heredoc_sigint = true;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void ft_init_signals(void)
{
	// struct termios	term;
	
	// term = g_minishell.original_term;
	// term.c_lflag &= ~ECHOCTL;
	// tcsetattr(STDERR_FILENO, TCSANOW, &term);
	// g_minishell.heredoc_sigint = false;
	// g_minishell.signint_child = false;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}

void	ft_clear_io_list(t_io_node **lst)
{
	t_io_node	*curr_node;
	t_io_node	*next;

	curr_node = *lst;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		ft_free_char2(curr_node -> expanded_value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*lst = NULL;
}

void	ft_clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	ft_clear_io_list(&(node -> io_list));
	free(node -> args);
	ft_free_char2(node -> expanded_args);
}
void	ft_recursive_clear_ast(t_node *node)
{
	if (!node)
		return ;
	if (node -> type == N_CMD)
		ft_clear_cmd_node(node);
	else
	{
		if (node->left)
			ft_recursive_clear_ast(node->left);
		if (node->right)
			ft_recursive_clear_ast(node->right);
	}
	free(node);
}

void	ft_clear_ast(t_node **ast)
{
	ft_recursive_clear_ast(*ast);
	*ast = NULL;
	ft_clear_token_list(&g_minishell.tokens);
}

static void	ft_clear_envlst(void)
{
	t_env	*envlst;
	t_env	*envlst_tofree;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		envlst_tofree = envlst;
		envlst = envlst->next;
		free(envlst_tofree);
	}
	g_minishell.envlst = NULL;
}


void ft_clean_ms(void)
{
	ft_garbage_collector(NULL, true);
	ft_clear_ast(&g_minishell.ast);
	ft_clear_envlst();
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
}

int	main(int argc, char **argv, char **env)
{
	((void)argc, (void)argv);
	ft_init_minishell(env);
	while (1)
	{
		ft_init_signals();
		g_minishell.line = readline(PROMPT);
		//verificas se ha argumento
		if (!g_minishell.line)
			ft_clean_ms(),
					ft_putstr_fd("exit\n", 1), exit(g_minishell.exit_s);
		//se houver argumento coloca no historico
		if (g_minishell.line[0])
			add_history(g_minishell.line);
		//tokenizaçao
		g_minishell.tokens = ft_tokenize();
		//verifica se nao ha tokenizacao, se nao continua
		if (!g_minishell.tokens)
			continue ;
		//parser
		//g_minishell.ast = ft_parse();
		//verifica se há erro no parse
		// if (g_minishell.parse_err.type)
		// {
		// 	ft_handle_parse_err();
		// 	continue ;
		// }
		//execução
		ft_start_execution();
	}
	ft_garbage_collector(NULL, true);
	return (ft_clean_ms(), g_minishell.exit_s);
}
