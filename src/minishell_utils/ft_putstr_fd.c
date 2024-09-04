/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:39:13 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/24 21:53:16 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t		len;

	if (s == NULL)
		return (0);
	len = ft_strlen(s);
	return ((int)write(fd, s, len));
}
