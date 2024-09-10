/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:38:05 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/21 06:23:49 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	else
	{
		i = 0;
		while (src[i] != '\0' && dst_len < size - 1)
		{
			dst[dst_len] = src[i];
			dst_len++;
			i++;
		}
		dst[dst_len] = '\0';
	}
	return (dst_len + ft_strlen(&src[i]));
}
