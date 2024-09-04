/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_no.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 07:32:55 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/06 02:32:19 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strs_create2(char original[4][4101], char *argv)
{
	char	path_pwd[4096];

	getcwd(path_pwd, sizeof(path_pwd));
	ft_strlcpy(original[0], "OLDPWD=a", 9);
	ft_strlcpy(original[1], "PWD=", 5);
	ft_strlcat(original[1], path_pwd,
		(ft_strlen(original[1]) + ft_strlen(path_pwd) + 1));
	ft_strlcpy(original[2], "SHLVL=0", 8);
	ft_strlcpy(original[3], "_=", 3);
	ft_strlcat(original[3], argv, (2 + ft_strlen(argv) + 1));
}

int	strs_create(char **strs, char *argv)
{
	char	original[4][4101];
	size_t	i;

	strs_create2(original, argv);
	i = 0;
	while (i < 4)
	{
		strs[i] = ft_strdup(original[i]);
		if (strs[i] == NULL)
		{
			envp_all_free(strs);
			return (0);
		}
		i += 1;
	}
	strs[i] = NULL;
	return (1);
}

int	envp_no(char *argv)
{
	char		**strs;

	strs = malloc(sizeof(char *) * (4 + 1));
	if (strs == NULL)
		return (0);
	if (!strs_create(strs, argv))
	{
		free (g_data);
		return (0);
	}
	if (!envlst_create(strs))
	{
		envp_all_free(strs);
		free (g_data);
		return (0);
	}
	if (!envp_create(g_data->envlst))
	{
		envp_all_free(strs);
		envlst_free();
		free (g_data);
		return (0);
	}
	envp_all_free(strs);
	return (1);
}
