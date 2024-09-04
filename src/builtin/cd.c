/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:54:49 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/06 01:54:52 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_change_env_pwds(char path_pwd[4096], char old_pwd[4096])
{
	t_env_node	*old;
	t_env_node	*now;

	old = check_envp("OLDPWD");
	if (old != NULL)
	{
		if (old->value != NULL)
			free(old->value);
		old->value = ft_strdup(old_pwd);
		if (old->value == NULL)
			return (0);
	}
	now = check_envp("PWD");
	if (now != NULL)
	{
		if (now->value != NULL)
			free(now->value);
		now->value = ft_strdup(path_pwd);
		if (now->value == NULL)
			return (0);
	}
	if (!envp_re_create(g_data->envlst))
		return (0);
	g_data->status = 0;
	return (1);
}

static int	cd_blt_sub(t_node_n *n)
{
	int	i;

	if (n->cmds[1] == NULL)
		return (1);
	if (n->cmds[1][0] == '-')
	{
		i = 1;
		while (n->cmds[1][i])
		{
			if (ft_isalnum(n->cmds[1][i]) || i == 3)
				break ;
			i++;
		}
		if (ft_isalnum(n->cmds[1][i]) || i == 3)
		{
			error_write("minishell: cd: -%s: invalid ", &n->cmds[1][1], 1);
			ft_putstr_fd("option\ncd: usage: cd [no option] [dir]\n", 2);
			return (0);
		}
	}
	return (1);
}

static char	*cd_home(char *cmd)
{
	char	*pwd;

	if (cmd == NULL)
	{
		pwd = ft_getenv("HOME");
		if (pwd == NULL)
		{
			error_write("minishell: cd: HOME not set\n", NULL, 1);
			return (NULL);
		}
	}
	else
		pwd = cmd;
	return (pwd);
}

static int	cd_blt2(char old_pwd[4096])
{
	char		path_pwd[4096];

	if (getcwd(path_pwd, sizeof(path_pwd)) != NULL)
	{
		if (cd_change_env_pwds(path_pwd, old_pwd) == 0)
			return (0);
	}
	else
	{
		perror("getcwd");
		g_data->status = 1;
		return (0);
	}
	return (1);
}

int	cd_blt(t_node_n *n)
{
	char		old_pwd[4096];
	char		*pwd;

	pwd = cd_home(n->cmds[1]);
	if (pwd == NULL)
		return (1);
	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		perror("getcwd");
		g_data->status = 1;
		return (0);
	}
	if (cd_blt_sub(n) == 0)
		return (1);
	if (chdir(pwd) != 0)
	{
		error_write("minishell: cd: %s: No such file or directory\n",
			pwd, 1);
		return (1);
	}
	if (!cd_blt2(old_pwd))
		return (0);
	return (1);
}
