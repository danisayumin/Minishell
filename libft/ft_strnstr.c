/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:45:30 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/29 18:03:32 by dsayumi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ocurrence;
	size_t	lil_len;
	size_t	c;

	ocurrence = NULL;
	lil_len = ft_strlen(little);
	c = 0;
	while (big[c] && c < len && lil_len)
	{
		if (!ft_strncmp((big + c), little, lil_len) && (c + lil_len <= len))
		{
			ocurrence = (char *)(big + c);
			break ;
		}
		c++;
	}
	if (!lil_len)
		ocurrence = (char *)big;
	return (ocurrence);
}
