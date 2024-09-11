/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:58:52 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/21 12:32:05 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**word_split(char **str_arr, int size, char *s, char c)
{
	size_t	i;
	int		word_count;
	size_t	j;

	i = 0;
	word_count = 0;
	while (word_count < size)
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		str_arr[word_count] = malloc((j - i) + 1);
		ft_memcpy((void *)str_arr[word_count], (const void *)&s[i], j - i);
		str_arr[word_count][j - i] = '\0';
		i = j;
		word_count++;
	}
	str_arr[word_count] = NULL;
	return (str_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	int		i;
	int		size;

	if (s == NULL)
		return (NULL);
	i = -1;
	size = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			size++;
	}
	str_arr = malloc((size + 1) * sizeof(char *));
	if (str_arr == NULL)
		return (NULL);
	str_arr = word_split(str_arr, size, (char *)s, c);
	return (str_arr);
}
