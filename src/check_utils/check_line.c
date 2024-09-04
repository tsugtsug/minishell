/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:12:37 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/10 21:32:28 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quart_messege(int flag)
{
	if (flag == 1)
	{
		error_write("minishell: syntax error near unclosed single quote\n",
			NULL, 258);
	}
	else if (flag == 2)
	{
		error_write("minishell: syntax error near unclosed double quote\n",
			NULL, 258);
	}
}

static int	quart_check(char *line)
{
	size_t		i;
	int			flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (flag == 0 && line[i] == '\'')
			flag = 1;
		else if (flag == 0 && line[i] == '"')
			flag = 2;
		else if (flag == 1 && line[i] == '\'')
			flag = 0;
		else if (flag == 2 && line[i] == '"')
			flag = 0;
		i += 1;
	}
	if (flag != 0)
	{
		quart_messege(flag);
		return (0);
	}
	return (1);
}

static int	check_space(char *line)
{
	size_t	i;

	if (line[0] == '\0')
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" \t", line[i]))
			return (1);
		i += 1;
	}
	return (0);
}

int	check_line(char *line)
{
	if (!check_space(line))
	{
		free(line);
		line = NULL;
		return (0);
	}
	if (!quart_check(line))
	{
		free(line);
		line = NULL;
		return (0);
	}
	return (1);
}
