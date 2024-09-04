/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 05:31:58 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:12:59 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	equal_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i += 1;
	return (i);
}

void	unset_error_message2(char *s)
{
	error_write("minishell: unset: `%s': not a valid identifier\n", s, 1);
}
