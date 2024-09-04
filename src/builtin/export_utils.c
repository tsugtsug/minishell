/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:29:27 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:11:04 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	identifier_check(const char *s)
{
	size_t		i;

	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (ft_strchr(IDENTIFIER, s[i]))
			return (0);
		i += 1;
	}
	return (1);
}

t_env_node	*check_envp(char *key)
{
	t_env_node	*node;

	node = g_data->envlst->top;
	while (node != NULL)
	{
		if (!ft_strcmp(key, node->key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*equal_join(char *key, char *value)
{
	char	*str;
	size_t	keylen;
	size_t	valuelen;

	keylen = ft_strlen(key);
	valuelen = 0;
	if (value != NULL)
		valuelen = ft_strlen(value);
	str = malloc(sizeof(char) * (keylen + valuelen + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, key, keylen + 1);
	if (value != NULL)
	{
		ft_strlcat(str, "=", keylen + 2);
		ft_strlcat(str, value, (keylen + valuelen + 2));
	}
	return (str);
}
