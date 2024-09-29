/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joscarlo <joscarlo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:17:33 by dsayumi-          #+#    #+#             */
/*   Updated: 2024/09/28 21:12:21 by joscarlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	ft_export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	ft_export_iterator(char **args, int i, int exit_s)
{
	char	*key;

	while (args[i])
	{
		if (ft_check_key(args[i]) == 0)
			exit_s = ft_export_err_msg(args[i]);
		else
		{
			key = ft_extract_key(args[i]);
			if (ft_env_entry_exists(key))
				ft_update_envlst(key, ft_extract_value(args[i]), false);
			else
			{
				ft_update_envlst(key, ft_extract_value(args[i]), true);
			}
		}
		i++;
	}
	return (exit_s);
}

static	void	ft_export_list(void)
{
	t_env	*list;
	size_t	i;

	list = get_mini()->envlst;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			i = 0;
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", (list->value)[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

int	ft_export(char **argv)
{
	int		i;
	int		exit_s;
	char	*str;

	exit_s = 0;
	i = 1;
	if (get_mini()->tokens->next == NULL)
		return (ft_export_list(), 0);
	str = get_mini()->tokens->next->value;
	if ((str[0] == '\"' || str[1] == '\"')
		|| (str[0] == '\'' || str[1] == '\''))
		return (1);
	return (ft_export_iterator(argv, i, exit_s));
}
