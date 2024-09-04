/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:50:17 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/01 01:45:24 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_free(void)
{
	long	status;

	status = g_data->status;
	envp_all_free(g_data->envp);
	envlst_free();
	free(g_data);
	g_data = NULL;
	printf("exit\n");
	exit (status);
}
