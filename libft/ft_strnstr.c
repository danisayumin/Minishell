/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:30 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/13 16:21:49 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	big_len;
	size_t	i;
	size_t	j;

	if (little[0] == '\0' || little == NULL)
		return ((char *)big);
	big_len = ft_strlen(big);
	if (len > big_len)
		len = big_len;
	i = 0;
	j = 0;
	while (i < len && big[i] != '\0' && little[j] != '\0')
	{	
		j = 0;
		while (big[i] != little[j])
			i++;
		while (big[i + j] == little[j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
