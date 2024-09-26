/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:00:59 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/26 18:49:02 by dsayumi-         ###   ########.fr       */
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
	ft_memset(get_mini(), 0, sizeof(t_minishell));
	get_mini()->environ = env;
	// get_mini()->stdin = dup(0);
	// get_mini()->stdout = dup(1);
	tcgetattr(STDIN_FILENO, &get_mini()->original_term);
}

static void	ft_start_execution(void)
{
	int	result;

	signal(SIGQUIT, ft_sigquit_handler);
	ft_init_tree(get_mini()->ast);
	if (get_mini()->heredoc_sigint)
	{
		ft_clear_ast(&get_mini()->ast);
		get_mini()->heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &get_mini()->original_term);
	result = ft_exec_node(get_mini()->ast, false);
	get_mini()->exit_s = result;
	ft_clear_ast(&get_mini()->ast);
}

int	main(int argc __attribute__((unused)), \
			char **argv __attribute__((unused)), char **env)
{
	int	exit_status;

	ft_init_minishell(env);
	while (1)
	{
		ft_init_signals();
		get_mini()->line = readline(PROMPT);
		if (!get_mini()->line)
			(ft_clean_ms(), ft_putstr_fd("exit\n", 1), exit(get_mini()->exit_s));
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
	exit_status = get_mini()->exit_s;
	ft_garbage_collector(NULL, true);
	return (ft_clean_ms(), exit_status);
}
