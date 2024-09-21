/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:38:36 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/21 16:50:31 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_handler(int num)
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

void	ft_sigquit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
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
