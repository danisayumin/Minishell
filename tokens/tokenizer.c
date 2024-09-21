/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:42:11 by danielasayu       #+#    #+#             */
/*   Updated: 2024/09/21 16:50:31 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenize(void)
{
	char	*line;
	t_token	*token_list;

	line = g_minishell.line;
	token_list = ft_tokenization_handler(line);
	free(line);
	g_minishell.line = NULL;
	return (token_list);
}
