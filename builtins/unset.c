/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:37:20 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/24 20:47:59 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	ft_unset_helper(char *key)
{
	t_env	*current;
	t_env	*prev;
	
	prev = NULL;
	current = get_mini()->envlst;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			if (prev)
				prev->next;
			else
				get_mini()->envlst = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	
}

int		ft_unset(char **args)
{
	int		i;
	bool	err;

	i = 1;
	if (!args[1])
		return (0);
	err = false;
	while (args[i])
	{
		if (!ft_check_key(args[i]))
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = true;
		}
		else
			ft_unset_helper(ft_garbage_collector(ft_extract_key(args[i]), false));
		i++;
	}
	return (err);
}
