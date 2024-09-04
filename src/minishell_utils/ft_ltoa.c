/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:52:41 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/13 17:05:02 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ltoa_count(unsigned long n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i += 1;
	}
	return (i);
}

static void	ltoa_helper(char *str, unsigned long n, size_t len, size_t sign)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (sign == 1 && (len - 1 - i) == 0)
			str[0] = '-';
		else
			str[len - 1 - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	str[len] = '\0';
}

char	*ft_ltoa(long status)
{
	char			*str;
	size_t			len;
	size_t			sign;
	unsigned long	u_num;

	sign = 0;
	if (status < 0)
	{
		u_num = (unsigned long)(status * -1);
		sign += 1;
	}
	else
		u_num = (unsigned long)status;
	len = ltoa_count(u_num) + sign;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ltoa_helper(str, u_num, len, sign);
	return (str);
}
