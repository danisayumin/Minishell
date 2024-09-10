/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:25:07 by joscarlo          #+#    #+#             */
/*   Updated: 2023/05/23 20:37:54 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	struct s_list	*current;
	struct s_list	*new_node;
	struct s_list	*ptr;

	if (lst == NULL)
		return (NULL);
	new_node = NULL;
	current = lst;
	while (current != NULL)
	{
		ptr = ft_lstnew(f(current->content));
		if (ptr)
			ft_lstadd_back(&new_node, ptr);
		else
			del(current->content);
		current = current->next;
	}
	return (new_node);
}
