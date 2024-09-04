/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykusano <ykusano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 04:39:34 by yokamura          #+#    #+#             */
/*   Updated: 2023/06/10 21:05:06 by ykusano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell.h"

void	ft_bzero(void *s, size_t n);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char	*dst, char *src, size_t dstsize);
char	*ft_strncpy(char *dst, char *src, size_t len);
size_t	ft_strlcat(char	*dst, char *src, size_t dstsize);
size_t	ft_strlen(char *s);
void	*ft_memcpy(void *dst, void *src, size_t n);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int num);
size_t	ft_cmd_count(char **strs);
long	ft_atol(const char *str);
char	*ft_ltoa(long status);
char	*ft_strndup(const char *s1, size_t n);
int		ft_putstr_fd(char *s, int fd);
void	error_write(char *s1, char *s2, long status);
char	*ft_getenv(char *str);
size_t	vers_strlen(char *s, char *end_s);
size_t	space_len(char *s);

#endif
