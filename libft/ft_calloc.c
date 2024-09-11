/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:46:30 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/20 23:10:50 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	sum;

	sum = nitems * size;
	if (sum != 0 && ((sum / nitems) != size))
		return (0);
	ptr = malloc(sum);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, sum);
	return ((void *)ptr);
}
