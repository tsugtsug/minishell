/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 06:53:25 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/06 17:09:00 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_sub(char *path, char *file, char *end, char *env)
{
	char	*rtn;

	while (*env)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(env, ':');
		if (end)
			ft_strncpy(path, env, end - env);
		else
			ft_strlcpy(path, env, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, file, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			rtn = ft_strdup(path);
			if (rtn == NULL)
				perror("strdup");
			return (rtn);
		}
		if (end == NULL)
			return (NULL);
		env = end + 1;
	}
	return (NULL);
}

static void	point_slash(char *file)
{
	if (file[0] == '.')
	{
		if (ft_strlen(file) == 1)
		{
			ft_putstr_fd("minishell: .: filename argument required\n", 2);
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
			exit (2);
		}
		else if (file[1] == '/' && ft_strlen(file) == 2)
		{
			ft_putstr_fd("minishell: ./: is a directory\n", 2);
			exit(126);
		}
	}
}

char	*search_path(char *file)
{
	char	path[PATH_MAX];
	char	*env;
	char	*end;
	char	*rtn;

	point_slash(file);
	if (file[0] == '.' && access(file, X_OK) == 0)
		return (file);
	if (file[0] == '/' && access(file, X_OK) == 0)
		return (file);
	env = ft_getenv("PATH");
	if (env == NULL)
		return (NULL);
	end = NULL;
	rtn = search_sub(path, file, end, env);
	free(file);
	return (rtn);
}
