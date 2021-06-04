/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 08:00:26 by prolling          #+#    #+#             */
/*   Updated: 2021/06/04 18:50:31 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

int		get_next_line(int fd, char **line);
size_t	ft_valid_fd(int fd);
size_t	ft_strlen(const char *s);
int		ft_update_buf_line(int fd, char *buf, char **line, size_t buf_filled);
size_t	ft_extend_line(char **line, size_t more_bytes);

#endif
