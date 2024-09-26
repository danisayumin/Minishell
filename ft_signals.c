/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:37:41 by dsayumi-          #+#    #+#             */
/*   Updated: 2024/09/26 17:57:00 by dsayumi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigquit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	ft_clear_line(void)
{
	printf("\033[2K\r");
}

void	ft_sigint_handler(int num)
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
		ft_clear_line();
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_init_signals(void)
{
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
