/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:30:28 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/22 16:47:14 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	ft_free_char2(char **tofree)
{
	size_t	i;

	if (!tofree)
		return ;
	i = 0;
	while (tofree[i])
		free(tofree[i++]);
	free(tofree);
}
