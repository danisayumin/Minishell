/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:58:07 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/21 06:04:17 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{	
	char	ch_int;

	ch_int = (char)c;
	while (*str)
	{
		if (*str == ch_int)
			return ((char *)str);
		str++;
	}
	if (ch_int == '\0')
		return ((char *)str);
	return (NULL);
}
