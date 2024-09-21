/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:30:28 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/21 20:17:06 by joscarlo         ###   ########.fr       */
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

char	*ft_strjoin_with(char const *s1, char const *s2, char c)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!c || !ft_strlen(s1) || !ft_strlen(s2))
		return (ft_strjoin(s1, s2));
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1 + 1;
	joined = ft_calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i++] = c;
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (joined);
}

char	*ft_strjoin_with_f(char *s1, char *s2, char c)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!c || !ft_strlen(s1) || !ft_strlen(s2))
		return (ft_strjoin(s1, s2));
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1 + 1;
	joined = ft_calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i++] = c;
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (free(s1), free(s2), joined);
}
