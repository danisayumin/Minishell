/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:42:11 by danielasayu       #+#    #+#             */
/*   Updated: 2024/09/28 13:47:55 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenize(void)
{
	char	*line;
	t_token	*token_list;

	line = get_mini()->line;
	if (line[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|", 2);
		ft_putstr_fd("'\n", 2);
		get_mini()->exit_s = 2;
		free(line);
		return (NULL);
	}
	token_list = ft_tokenization_handler(line);
	free(line);
	get_mini()->line = NULL;
	return (token_list);
}
