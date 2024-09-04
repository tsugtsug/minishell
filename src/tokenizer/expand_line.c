/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:01:07 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/13 00:24:52 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expansion_help(char *str, char *s, size_t *i, int f)
{
	char		*mstr;

	mstr = NULL;
	if (s[1] == '?')
	{
		mstr = ft_ltoa(g_data->status);
		*i = 2;
	}
	else
		mstr = env_str_quart(s, i, f);
	if (mstr == NULL)
		return (NULL);
	str = expand_join(str, mstr, ft_strlen(mstr));
	free(mstr);
	return (str);
}

static char	*expand_line2(char *new, char *s, size_t *j, int f)
{
	char	*str;
	int		flag;

	str = NULL;
	flag = dollar_check(s, f);
	if (f != 1 && flag == 1)
		str = expansion_help(new, s, j, f);
	else if (f != 1 && flag == 3)
		str = expand_join(new, &s[*j], 0);
	else if (f != 1 && flag == 2)
	{
		*j = 2;
		str = expand_join(new, &s[*j], 0);
	}
	else if (f != 1 && flag == -1)
	{
		while (s[*j] && ft_strchr(NV, s[*j]))
			*j += 1;
		str = expand_join(new, &s[*j], 0);
	}
	else
		str = expand_join(new, s, 1);
	return (str);
}

int	quart_sign_check(char c, int f)
{
	int	r_num;

	r_num = f;
	if (f == 0 && c == '\'')
		r_num = 1;
	else if (f == 0 && c == '"')
		r_num = 2;
	else if (f == 1 && c == '\'')
		r_num = 0;
	else if (f == 2 && c == '"')
		r_num = 0;
	return (r_num);
}

char	*expand_line(char *s)
{
	size_t	i;
	size_t	j;
	int		f;
	char	*new;

	new = NULL;
	f = 0;
	i = fill_space(s);
	while (s[i])
	{
		f = quart_sign_check(s[i], f);
		j = 1;
		new = expand_line2(new, &s[i], &j, f);
		i += j;
		if (new == NULL)
			break ;
	}
	free(s);
	return (new);
}
