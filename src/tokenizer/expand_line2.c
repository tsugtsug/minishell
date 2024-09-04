/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:12:09 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/09 17:12:36 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quart_str(char *value)
{
	char	*str;
	size_t	len;

	str = NULL;
	len = ft_strlen(value);
	str = malloc(sizeof(char) * (len + 3));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, "\"", 2);
	ft_strlcat(str, value, (len + 2));
	ft_strlcat(str, "\"", (len + 3));
	return (str);
}

static char	*env_str_quart2(char *s, size_t *i, int f)
{
	t_env_node	*envl;
	char		*str;

	*i = 0;
	envl = g_data->envlst->top;
	while (envl != NULL)
	{
		if (!ft_strncmp(envl->key, &s[*i + 1], ft_strlen(envl->key)))
		{
			if (f != 2 && !ft_strncmp("export ", g_data->line, 7))
				str = quart_str(envl->value);
			else
				str = ft_strdup(envl->value);
			*i += ft_strlen(envl->key) + 1;
			return (str);
		}
		envl = envl->next;
	}
	return (NULL);
}

char	*env_str_quart(char *s, size_t *i, int f)
{
	char		*str;

	str = NULL;
	str = env_str_quart2(s, i, f);
	if (str == NULL)
		return (NULL);
	return (str);
}
