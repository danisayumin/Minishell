/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:00:59 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/28 21:21:53 by dsayumi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*get_mini(void)
{
	static t_minishell	*mini;

	if (!mini)
	{
		mini = malloc(sizeof(t_minishell));
		ft_memset(mini, 0, sizeof(t_minishell));
	}
	return (mini);
}

static void	ft_init_minishell(char **env)
{
	t_minishell	*mini;

	mini = get_mini();
	ft_memset(mini, 0, sizeof(t_minishell));
	mini->environ = env;
	ft_init_envlst();
	mini->stdin = dup(STDIN_FILENO);
	mini->stdout = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &mini->original_term);
}

static void	ft_start_execution(void)
{
	t_minishell	*mini;

	mini = get_mini();
	signal(SIGQUIT, ft_sigquit_handler);
	ft_init_tree(mini->ast);
	if (mini->heredoc_sigint)
	{
		ft_clear_ast(&mini->ast);
		mini->heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->original_term);
	mini->exit_s = ft_exec_node(mini->ast, false);
	ft_clear_ast(&mini->ast);
}

int	main(int argc __attribute__((unused)), \
			char **argv __attribute__((unused)), char **env)
{
	int	exit_status;

	ft_init_minishell(env);
	exit_status = get_mini()->exit_s;
	while (1)
	{
		ft_init_signals();
		get_mini()->line = readline(PROMPT);
		if (!get_mini()->line)
			(ft_clean_ms(), ft_putstr_fd("exit\n", 1), exit(exit_status));
		if (get_mini()->line[0])
			add_history(get_mini()->line);
		get_mini()->tokens = ft_tokenize();
		if (!get_mini()->tokens)
			continue ;
		get_mini()->ast = ft_parse();
		if (get_mini()->parse_err.type)
			ft_handle_parse_err();
		else
			ft_start_execution();
	}
	ft_garbage_collector(NULL, true);
	return (ft_clean_ms(), exit_status);
}
