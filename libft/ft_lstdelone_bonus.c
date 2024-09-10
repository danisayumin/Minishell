/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:09:26 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/23 20:15:44 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	struct s_list	*ptr;

	if (lst == NULL)
		return ;
	ptr = lst;
	lst = lst->next;
	del(ptr->content);
	free(ptr);
}
