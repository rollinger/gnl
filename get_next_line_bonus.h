/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 08:00:26 by prolling          #+#    #+#             */
/*   Updated: 2021/06/07 12:04:02 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef MAX_FD
#  define MAX_FD 179
# endif

int		get_next_line(int fd, char **line);
size_t	ft_valid_fd(int fd);
int		ft_reload_buf(int fd, char *buf, size_t start, size_t end);
void	ft_append_buf_line(char **line, char *buf, int c);
size_t	ft_shift_buf(char *buf, char *nl_pos);
/* Util Functions */
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
size_t	ft_strclen(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);

#endif