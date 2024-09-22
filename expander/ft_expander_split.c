/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:04:59 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/22 18:51:23 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_skip_word(char const *s, size_t *i)
{
	char quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

static char **ft_allocater(char const *s, char **strs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			ft_skip_word(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

static void	ft_words_filler(char const *s, char **strs, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (s[(*i)] && s[(*i)] != ' ')
	{
		if (s[(*i)] != '\'' && s[(*i)] != '"')
			strs[j][k++] = s[(*i)++];
		else
		{
			quotes = s[(*i)++];
			strs[j][k++] = quotes;
			while (s[(*i)] != quotes)
				strs[j][k++] = s[(*i)++];
			strs[j][k++] = s[(*i)++];
		}
	}
}

static char	**ft_filler(char const *s, char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != ' ')
		{
			ft_words_filler(s, strs, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

char	**ft_expander_split(char const *s)
{
	size_t		count;
	char		**strs;
	char		**tofree;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ++count)
			ft_skip_word(s, &i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	tofree = strs;
	strs = ft_allocater(s, strs);
	if (!strs || !count)
		return (ft_free_char2(tofree), NULL);
	return (ft_filler(s, strs));
}
