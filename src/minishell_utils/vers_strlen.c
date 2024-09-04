/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vers_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:49:54 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/10 20:50:14 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	vers_strlen(char *s, char *end_s)
{
	size_t		len;

	if (s == NULL)
		return (0);
	if (end_s == NULL)
		return (ft_strlen(s));
	len = 0;
	while (s[len] && !ft_strchr(end_s, s[len]))
		len += 1;
	return (len);
}
