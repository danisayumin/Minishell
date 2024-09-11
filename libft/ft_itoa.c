/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:32:56 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/21 12:48:20 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(long int n)
{
	if (n < 0)
		return (1 + nbrlen(-n));
	if ((n / 10) == 0)
		return (1);
	else
		return (1 + nbrlen(n / 10));
}

static void	convert(long int n, char *num, long int i)
{
	if (n < 0)
	{
		num[0] = '-';
		n *= -1;
	}
	if (n >= 10)
	{
		convert((n / 10), num, (i - 1));
	}
	num[i] = n % 10 + 48;
}

char	*ft_itoa(int n)
{
	char	*str_int;
	int		len;

	len = nbrlen(n);
	str_int = (char *)malloc(len + 1);
	if (str_int == NULL)
		return (NULL);
	str_int[len] = '\0';
	convert(n, str_int, --len);
	return (str_int);
}
