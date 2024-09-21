/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:12:07 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/21 19:12:25 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_out(t_io_node *io_list, int *status)
{
	int		fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_err_msg(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_write(io_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_in(t_io_node *io_list, int *status)
{
	int		fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_err_msg(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->expanded_value[0], O_RDONLY);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_read(io_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_append(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expanded_value || io_list->expanded_value[1])
	{
		*status = ft_err_msg(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_write(io_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (0);
}
