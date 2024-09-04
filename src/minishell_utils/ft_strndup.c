/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:30:32 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/25 18:30:34 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;

	str = malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, n + 1);
	return (str);
}
