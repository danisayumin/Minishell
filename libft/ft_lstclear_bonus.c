/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:16:34 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/23 20:20:03 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	struct s_list	*ptr;

	while (*lst != NULL)
	{
		ptr = *lst;
		*lst = ptr->next;
		del(ptr->content);
		free(ptr);
	}
}
