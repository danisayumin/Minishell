/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:42:11 by danielasayu       #+#    #+#             */
/*   Updated: 2024/09/24 19:12:58 by dsayumi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenize(void)
{
	char	*line;
	t_token	*token_list;

	line = get_mini()->line;
	token_list = ft_tokenization_handler(line);
	free(line);
	get_mini()->line = NULL;
	return (token_list);
}
