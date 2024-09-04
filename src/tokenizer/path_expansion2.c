/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_expansion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 07:26:16 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/11 20:26:39 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_str2(char *s, size_t *i)
{
	t_env_node	*envl;
	char		*str;

	*i = 0;
	str = NULL;
	envl = g_data->envlst->top;
	while (envl != NULL)
	{
		if (!ft_strncmp(envl->key, &s[*i + 1], ft_strlen(envl->key)))
		{
			str = ft_strdup(envl->value);
			*i += ft_strlen(envl->key) + 1;
			return (str);
		}
		envl = envl->next;
	}
	return (NULL);
}

char	*env_str(char *s, size_t *i)
{
	char		*str;

	str = NULL;
	str = env_str2(s, i);
	if (str == NULL)
		return (NULL);
	return (str);
}

static int	dollar_check2(const char *s)
{
	t_env_node	*p;
	size_t		i;

	i = 1;
	if (!ft_strchr(HEAD_ENV, s[i]))
		return (0);
	p = g_data->envlst->top;
	while (p != NULL)
	{
		if (s[i] == '?')
			return (1);
		else if ((!ft_strncmp(p->key, &s[i], ft_strlen(p->key)))
			&& ft_strchr(NO_ENV, s[i + ft_strlen(p->key)]))
			return (1);
		p = p->next;
	}
	return (-1);
}

int	dollar_check(const char *s, int f)
{
	if (s[0] == '$' && ft_strchr(" \t~`!@#$%^&*()-+=[]{}:;<>.,/\n", s[1]))
		return (0);
	if (f == 0 && s[0] == '$' && ft_strchr("'\"", s[1]))
		return (3);
	if (s[0] == '$' && ft_strchr("0123456789", s[1]))
		return (2);
	if (s[0] == '$')
		return (dollar_check2(s));
	return (0);
}
