/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 04:36:07 by yokamura          #+#    #+#             */
/*   Updated: 2023/05/23 04:44:20 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*rtn;
	int		i;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	rtn = (char *)malloc(i + 1);
	if (rtn == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		rtn[i] = s1[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
