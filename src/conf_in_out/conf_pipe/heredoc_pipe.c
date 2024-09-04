/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:17:14 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/01 22:52:00 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename_heredoc(int i)
{
	char	*rtn;

	if (i == 0)
		rtn = (char *)malloc(sizeof(char) * 9);
	else
		rtn = (char *)malloc(sizeof(char) * 10);
	if (rtn == NULL)
		return (NULL);
	rtn[0] = '.';
	rtn[1] = 'h';
	rtn[2] = 'e';
	rtn[3] = 'r';
	rtn[4] = 'e';
	rtn[5] = 'd';
	rtn[6] = 'o';
	rtn[7] = 'c';
	if (i == 0)
		rtn[8] = '\0';
	else
	{
		rtn[8] = i + '0';
		rtn[9] = '\0';
	}
	return (rtn);
}

static char	*write_sub(char *joined, int i)
{
	char	*filename;

	filename = filename_heredoc(i);
	if (filename == NULL)
	{
		g_data->status = 1;
		free(joined);
		return (NULL);
	}
	return (filename);
}

static int	write_heredoc_file(t_node_n *n, char *joined, int i)
{
	int		fd;
	char	*filename;

	filename = write_sub(joined, i);
	if (filename == NULL)
		return (1);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		free(joined);
		free(filename);
		g_data->status = 1;
		return (1);
	}
	if (i != 0)
		n->filename = filename;
	else
		free(filename);
	write(fd, joined, ft_strlen(joined));
	free(joined);
	return (0);
}

int	heredoc_pipe(char *delimiter, t_node_n *n, int i)
{
	char	*joined;

	set_signal_heredoc();
	joined = joined_create(delimiter);
	if (joined == NULL)
		return (1);
	joined = heredoc_expand(joined);
	if (joined == NULL)
		return (1);
	if (n == NULL)
		return (0);
	if (write_heredoc_file(n, joined, i) == 1)
		return (1);
	return (0);
}
