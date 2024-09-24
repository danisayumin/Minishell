/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:38:36 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/24 19:12:58 by dsayumi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_handler(int num)
{
	(void)num;
	if (get_mini()->signint_child)
	{
		ft_putstr_fd("\n", 1);
		get_mini()->signint_child = false;
		get_mini()->heredoc_sigint = true;
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
	
	// term = get_mini()->original_term;
	// term.c_lflag &= ~ECHOCTL;
	// tcsetattr(STDERR_FILENO, TCSANOW, &term);
	// get_mini()->heredoc_sigint = false;
	// get_mini()->signint_child = false;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
