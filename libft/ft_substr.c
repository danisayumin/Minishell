/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 08:48:22 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/21 09:19:44 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub_s;

	s_len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len - start > len)
		sub_s = malloc(len + 1);
	else
		sub_s = malloc((s_len - start) + 1);
	if (sub_s == NULL)
		return (NULL);
	ft_strlcpy(sub_s, &s[start], (len + 1));
	return (sub_s);
}
