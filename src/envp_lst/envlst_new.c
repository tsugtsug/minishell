/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:36 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/01 01:41:36 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*envlst_new(void)
{
	t_env_lst	*lst;

	lst = malloc(sizeof(t_env_lst));
	if (lst == NULL)
		return (NULL);
	lst->top = NULL;
	lst->size = 0;
	return (lst);
}
