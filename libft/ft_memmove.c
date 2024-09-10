/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:42:43 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/13 14:43:54 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	if (dest == NULL)
		return (NULL);
	i = 1;
	if (dest > src)
	{
		while (i <= n)
		{
			((unsigned char *)dest)[n - i] = ((unsigned char *)src)[n - i];
			i++;
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
