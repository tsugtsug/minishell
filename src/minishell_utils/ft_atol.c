/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:46:28 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/23 20:46:38 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	atol_space(const unsigned char *ntr, int *sign)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (('\t' <= ntr[i] && ntr[i] <= '\r') || ntr[i] == ' ')
		i++;
	while (ntr[i + j] == '+' || ntr[i + j] == '-')
	{
		if (ntr[i + j] == '-')
			*sign *= -1;
		j++;
		if (j == 2)
		{
			*sign = 0;
			return (i);
		}
	}
	return (i + j);
}

static int	over_check(unsigned int long s_div, unsigned int s_mod, int sign)
{
	unsigned int long	ov_div;
	unsigned int		ov_mod;
	unsigned int long	un_div;
	unsigned int		un_mod;

	ov_div = LONG_MAX / 10;
	ov_mod = LONG_MAX % 10;
	un_div = LONG_MIN / 10 * -1;
	un_mod = LONG_MIN % 10 * -1;
	if (sign == 1 && (ov_div < s_div || (ov_div == s_div && ov_mod < s_mod)))
		return (1);
	if (sign == -1 && (un_div < s_div || (un_div == s_div && un_mod < s_mod)))
		return (-1);
	return (0);
}

long	ft_atol(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long int	s1;
	unsigned int		s2;
	const unsigned char	*ntr;

	ntr = (const unsigned char *)str;
	sign = 1;
	i = atol_space (ntr, &sign);
	if (sign == 0)
		return (0);
	s1 = 0;
	while (ft_isdigit(ntr[i]))
	{
		s2 = ntr[i] - '0';
		if (over_check(s1, s2, sign) == 1)
			return (LONG_MAX);
		if (over_check(s1, s2, sign) == -1)
			return (LONG_MIN);
		s1 = s1 * 10 + s2;
		i++;
	}
	return ((long)(s1 * sign));
}
