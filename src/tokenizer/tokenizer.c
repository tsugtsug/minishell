/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:53:56 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/13 00:31:25 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quart_delete(t_token_l *lst)
{
	t_token_n	*tmp;

	tmp = lst->top;
	while (tmp != NULL)
	{
		if (tmp->type >= QUOTE && tmp->type <= QQUOTE)
		{
			delete_helper(lst, tmp);
			tmp = lst->top;
		}
		else
			tmp = tmp->next;
	}
}

static int	quort_only(void)
{
	t_env_node	*env;
	size_t		i;

	if ((g_data->line[0] == '\'' && g_data->line[1] == '\'')
		|| (g_data->line[0] == '"' && g_data->line[1] == '"'))
	{
		env = check_envp("_");
		env->value[0] = '\0';
		i = 0;
		while (ft_strncmp(g_data->envp[i], "_=", 2) != 0)
			i += 1;
		free(g_data->envp[i]);
		g_data->envp[i] = equal_join(env->key, env->value);
		if (g_data->envp[i] == NULL)
		{
			free(g_data->line);
			return (0);
		}
		ft_putstr_fd("minishell: : command not found\n", 2);
		g_data->status = 127;
		free(g_data->line);
		return (0);
	}
	return (1);
}

int	tokenizer(void)
{
	t_token_l	*lst;

	if (!quort_only())
		return (0);
	lst = space_split(g_data->line);
	if (lst == NULL)
		return (0);
	type_classify(lst);
	quart_delete(lst);
	if (!word_join(lst))
		return (0);
	delete_node(lst);
	if (syntax_error(lst) == 0)
		return (0);
	if (!set_under_env(lst))
		return (0);
	g_data->tok = lst;
	return (1);
}
