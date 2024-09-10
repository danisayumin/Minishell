/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:30:59 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/23 19:39:46 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*ptr;

	ptr = (struct s_list *)malloc(sizeof(struct s_list));
	if (ptr == NULL)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
