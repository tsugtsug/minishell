/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:29:27 by ykusano           #+#    #+#             */
/*   Updated: 2023/06/02 18:59:49 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_minishell(char *s1, char *s2)
{
	char	*rtn;
	size_t	i;
	size_t	j;

	rtn = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (rtn == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
	{
		while (s1[i])
			rtn[j++] = s1[i++];
		i = 0;
	}
	while (s2[i])
		rtn[j++] = s2[i++];
	rtn[j++] = '\n';
	rtn[j] = '\0';
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (rtn);
}

char	*joined_create(char *delimiter)
{
	char	*line;
	char	*joined;

	joined = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			if (joined == NULL)
				joined = ft_strdup("");
			if (joined == NULL)
				return (NULL);
			break ;
		}
		joined = strjoin_minishell(joined, line);
	}
	return (joined);
}

void	reset_fd(void)
{
	dup2(g_data->save_out, STDOUT_FILENO);
	dup2(g_data->pipe[0][0], STDIN_FILENO);
	close(g_data->pipe[0][1]);
	close(g_data->pipe[0][0]);
}

int	heredoc(char *delimiter)
{
	char	*joined;

	if (pipe(g_data->pipe[0]) < 0)
	{
		perror("pipe");
		g_data->status = 1;
		return (-1);
	}
	set_signal_heredoc();
	joined = joined_create(delimiter);
	if (joined == NULL)
	{
		reset_fd();
		return (0);
	}
	joined = heredoc_expand(joined);
	if (joined == NULL)
		return (-1);
	dup2(g_data->pipe[0][1], STDOUT_FILENO);
	printf("%s", joined);
	if (joined != NULL)
		free(joined);
	reset_fd();
	return (0);
}
