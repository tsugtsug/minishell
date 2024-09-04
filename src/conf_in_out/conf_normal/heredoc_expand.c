/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:59:59 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/11 19:11:51 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_check_ex2(const char *s)
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

static int	dollar_check_ex(const char *s)
{
	if (s[0] == '$' && ft_strchr(NO_ENV, s[1]))
		return (0);
	if (s[0] == '$' && ft_strchr("0123456789", s[1]))
		return (2);
	if (s[0] == '$')
	{
		return (dollar_check_ex2(s));
	}
	return (0);
}

static char	*heredoc_expand2(char *new, char *s, size_t *j)
{
	char	*str;
	int		f;

	f = dollar_check_ex(s);
	str = NULL;
	if (f == 1)
		str = expansion_help2(new, s, j);
	else if (f == 2)
	{
		*j = 2;
		str = expand_join(new, &s[*j], 0);
	}
	else if (f == -1)
	{
		while (s[*j] && ft_strchr(NV, s[*j]))
			*j += 1;
		str = expand_join(new, &s[*j], 0);
	}
	else
		str = expand_join(new, s, 1);
	return (str);
}

char	*heredoc_expand(char *s)
{
	char	*str;
	size_t	j;
	char	*free_s;

	if (s[0] == '\0')
		return (s);
	str = NULL;
	free_s = s;
	while (*s)
	{
		j = 1;
		str = heredoc_expand2(str, s, &j);
		s += j;
		if (str == NULL)
		{
			free(free_s);
			return (NULL);
		}
	}
	free(free_s);
	return (str);
}
