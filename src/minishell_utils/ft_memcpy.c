/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:55:29 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/23 19:55:55 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	unsigned char		*d_cpy;
	unsigned char		*s_cpy;

	d_cpy = (unsigned char *)dst;
	s_cpy = (unsigned char *)src;
	if (d_cpy == s_cpy)
		return (dst);
	while (n--)
	{
		*d_cpy = *s_cpy;
		d_cpy++;
		s_cpy++;
	}
	return (dst);
}
