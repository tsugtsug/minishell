/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_create.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 07:11:11 by ykusano           #+#    #+#             */
/*   Updated: 2023/05/31 23:25:04 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_CREATE_H
# define ENVP_CREATE_H

# include <stdlib.h>

void	envp_all_free(char **strs);
int		envp_re_create(t_env_lst *lst);
int		envp_create(t_env_lst *lst);

#endif
