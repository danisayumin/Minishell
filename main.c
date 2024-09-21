/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:00:59 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/21 20:33:15 by joscarlo         ###   ########.fr       */
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

static void	ft_start_execution(void)
{
	signal(SIGQUIT, ft_sigquit_handler);
	ft_init_tree(g_minishell.ast);
	if (g_minishell.heredoc_sigint)
	{
		ft_clear_ast(&g_minishell.ast);
		g_minishell.heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
	g_minishell.exit_s = ft_exec_node(g_minishell.ast, false);
	ft_clear_ast(&g_minishell.ast);
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
		g_minishell.ast = ft_parse();
		//verifica se há erro no parse
		if (g_minishell.parse_err.type)
		{
			ft_handle_parse_err();
			continue ;
		}
		//execução
		ft_start_execution();
	}
	ft_garbage_collector(NULL, true);
	return (ft_clean_ms(), g_minishell.exit_s);
}
