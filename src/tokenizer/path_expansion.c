/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:10:32 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/06 09:12:22 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion_help2(char *str, char *s, size_t *i)
{
	char	*mstr;

	mstr = NULL;
	if (s[1] == '?')
	{
		mstr = ft_ltoa(g_data->status);
		*i = 2;
	}
	else
		mstr = env_str(s, i);
	if (mstr == NULL)
		return (NULL);
	str = expand_join(str, mstr, ft_strlen(mstr));
	free(mstr);
	return (str);
}

char	*expand_join(char *s1, char *s2, size_t len)
{
	size_t		len1;
	char		*str;
	size_t		i;

	len1 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	str = malloc(sizeof(char) * (len1 + len + 1));
	if (str == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(str, s1, (len1 + 1));
	i = 0;
	while (i < len)
	{
		str[i + len1] = s2[i];
		i += 1;
	}
	str[i + len1] = '\0';
	if (s1 != NULL)
		free(s1);
	return (str);
}
