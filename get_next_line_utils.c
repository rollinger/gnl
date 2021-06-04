/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:57 by prolling          #+#    #+#             */
/*   Updated: 2021/06/04 18:53:21 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	int_len;

	int_len = 0;
	while (s[int_len] != '\0')
		int_len++;
	return (int_len);
}

/*
* Valid file descriptors must be positive and not exceed the MAX_FD definition
* return 0: not valid FD
* return 1: valid FD
*/
size_t	ft_valid_fd(int fd)
{
	if (fd < 0 || fd > MAX_FD)
		return (0);
	else
		return (1);
}

/*
* Update the buffer and extends the line
* fd			= file descriptor
* *buf			= static buffer at fd
* **line		= line to extend
* buf_filled	= state [buf_filled, line_filled]
* Returns number of bytes read
*/
int	ft_update_buf_line(int fd, char *buf, char **line, size_t buf_filled)
{
	int	nb_read;

	nb_read = read(fd, (void *)&buf[buf_filled], BUFFER_SIZE - buf_filled);
	if (nb_read > 0)
		ft_extend_line(line, nb_read);
	return (nb_read);
}

/*
* duplicates the <*line> and extends it, so it can hold at least <more_bytes>
* more bytes. the extention of bytes is bzero'ed
* Returns the total space allocated <old_length + more_bytes>
*/
size_t	ft_extend_line(char **line, size_t more_bytes)
{
	size_t	old_length;
	size_t	i;
	char	*new_line;

	old_length = ft_strlen(*line);
	new_line = (char *)malloc(sizeof(char) * (old_length + more_bytes));
	if (!new_line)
		return (0);
	i = 0;
	while (i++ < old_length)
		new_line[i] = *line[i];
	while (i++ < (old_length + more_bytes))
		new_line[i] = '\0';
	free(*line);
	*line = new_line;
	return (old_length + more_bytes);
}
