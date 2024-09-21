/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_appenders.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:11:07 by danielasayu       #+#    #+#             */
/*   Updated: 2024/09/21 16:50:31 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append_separator(t_token_type type, char **line_ptr,
	t_token **token_list)
{
	t_token	*token;

	token = ft_new_token(NULL, type);
	if (!token)
		return (0);
	ft_token_list_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT || type == T_OR || type == T_AND)
		(*line_ptr)++;
	return (1);
}

int	ft_append_identifier(char **line_ptr, t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !ft_is_separator(tmp_line + i))
	{
		if (ft_is_quote(tmp_line[i]))
		{
			if (!ft_skip_quotes(tmp_line, &i))
				return (ft_print_quote_err(tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = ft_new_token(value, T_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	*line_ptr += i;
	return (ft_token_list_add_back(token_list, token), 1);
}
