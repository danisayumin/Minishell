/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:17:21 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/21 09:44:05 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = malloc((s1_len + s2_len) + 1);
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s1, (s1_len + 1));
	ft_strlcpy(&new_s[s1_len], s2, (s2_len + 1));
	return (new_s);
}
