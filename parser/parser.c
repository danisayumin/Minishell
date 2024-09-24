#/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielasayuminitta <danielasayuminitta@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:39:21 by danielasayu       #+#    #+#             */
/*   Updated: 2024/09/14 23:39:21 by danielasayu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_term(void)
{
	if (get_mini()->parse_err.type)
		return (NULL);
	else
		return (ft_get_simple_cmd());
}

t_node	*ft_expression(int min_prec)
{
	t_node			*left;
	t_node			*right;
	int				n_prec;
	t_token_type	op;

	if (get_mini()->parse_err.type || !get_mini()->curr_token)
		return (NULL);
	left = ft_term();
	if (!left)
		return (NULL);
	while (ft_curr_token_is_binop() && ft_curr_token_prec() >= min_prec)
	{
		op = get_mini()->curr_token->type;
		ft_get_next_token();
		if (!get_mini()->curr_token)
			return (ft_set_parse_err(E_SYNTAX), left);
		n_prec = ft_prec(op) + 1;
		right = ft_expression(n_prec);
		if (!right)
			return (left);
		left = ft_combine(op, left, right);
		if (!left)
			return (ft_clear_ast(&left), ft_clear_ast(&right), NULL);
	}
	return (left);
}

t_node	*ft_combine(t_token_type op, t_node *left, t_node *right)
{
	t_node	*node;

	if (get_mini()->parse_err.type)
		return (NULL);
	node = ft_new_node(ft_get_node_type(op));
	if (!node)
		return (ft_set_parse_err(E_MEM), NULL);
	node -> left = left;
	node -> right = right;
	return (node);
}

t_node	*ft_parse(void)
{
	t_node	*ast;

	get_mini()->curr_token = get_mini()->tokens;
	ast = ft_expression(0);
	if (get_mini()->curr_token)
		return (ft_set_parse_err(E_SYNTAX), ast);
	return (ast);
}
