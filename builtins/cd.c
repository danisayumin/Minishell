/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsayumi- <dsayumi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:09:05 by joscarlo          #+#    #+#             */
/*   Updated: 2024/09/28 18:52:21 by dsayumi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_change_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 1);
	if (!cwd)
		return (0);
	return (ft_update_envlst("PWD", cwd, false), 0);
}

static int	ft_cd_home(void)
{
	char	*home;

	ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
	home = ft_get_envlst_val("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (ft_update_envlst("PWD", home, false), 0);
	return (1);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(char **argv)
{
	char	*path;

	if (argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	path = argv[1];
	if (!path)
		return (ft_cd_home());
	if (chdir(path) != ENO_SUCCESS)
		return (ft_cd_err_msg(path));
	ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
	return (ft_change_pwd());
}
