/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:08:38 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/21 05:57:28 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	ch_int;

	i = ft_strlen((char *)str);
	ch_int = (char)c;
	if (ch_int == '\0')
		return ((char *)&str[i]);
	else
	{
		i--;
		while (i >= 0)
		{
			if (str[i] == ch_int)
				return ((char *)&str[i]);
			i--;
		}
	}
	return (NULL);
}
