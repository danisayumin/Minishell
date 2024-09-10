/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:13:52 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/27 13:15:01 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if (n <= 0 || !str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] == str2[i] && i < (n - 1) && (str1[i] || str2[i]) != '\0')
		i++;
	return (str1[i] - str2[i]);
}
