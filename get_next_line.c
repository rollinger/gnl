/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:39 by prolling          #+#    #+#             */
/*   Updated: 2021/06/05 21:12:58 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* Write a function which returns a line read from a file descriptor, without
* the newline
* Parameters
* #1. file descriptor for reading
* #2. The value of what has been read
* Function Returns:
* 1 : A line has been read
* 0 : EOF has been reached
* -1 : An error happened
*
* fd_buffer => idx=FD [MAX_FD][BUFFER_SIZE + \0]
* MAX_FD: max number of file descriptors. defined by the system.
* BUFFER_SIZE: optimal buffer size - set by OS/Compilation. Default is 4096 byte
*
* Algorithm:
* GOAL: Read one line at a time from fd to line. (buf must hold state of n fd
* 	between gnl calls)
* 		- Read the fd content (buffer-block-wise) until \n or EOF is encountered
* 		 in the buffer or the BUFFER_SIZE is full (and no \n/EOF).
* 		- If \n/EOF is in the buf, copy left_part to line and move right part
* 		to start. (actual gnl.) next gnl call will fill up the buf if possible.
* 		- If no \n/EOF is in buf, read (BUFFER_SIZE - fragment_length) bytes
* 		to buf start appending it to buf content.
* 	- Return (1) if \n\0 string is in line.
* 	- Return (0) if fd has encountered EOF
* 	- Return (-1) on error
*/
int	get_next_line(int fd, char **line)
{
	static char	fd_buf[MAX_FD][BUFFER_SIZE + 1];
	char		*nl_pos;
	size_t		shifted;
	size_t		eof;

	*line = (char *)malloc(sizeof(char));
	if (!ft_valid_fd(fd) || BUFFER_SIZE <= 0 || !(*line))
		return (-1);
	while (ft_strchr((const char *)fd_buf[fd], '\n') == 0)
	{
		ft_append_buf_line(line, fd_buf[fd], '\0');
		ft_bzero((void *)fd_buf[fd], BUFFER_SIZE + 1);
		ft_reload_buf(fd, fd_buf[fd], 0, BUFFER_SIZE + 1);
	}
	nl_pos = ft_strchr((const char *)fd_buf[fd], '\n');
	ft_append_buf_line(line, fd_buf[fd], '\n');
	shifted = ft_shift_buf(fd_buf[fd], nl_pos);
	eof = ft_reload_buf(fd, fd_buf[fd], shifted, BUFFER_SIZE + 1);
	if (eof == 0)
		return (0);
	return (1);
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
* Reloads the <buf> at <fd> via the read() call from start to end
* Returns the number of bytes read; 0 if EOF
*/
int	ft_reload_buf(int fd, char *buf, size_t start, size_t end)
{
	int	nb_read;

	nb_read = read(fd, (void *)&buf[start], end - start - 1);
	return (nb_read);
}

/*
* Appends the <buf> until <c> to the end of <*line> making a bigger newline
* string and replacing *line.
*/
void	ft_append_buf_line(char **line, char *buf, int c)
{
	char	*newline;
	char	*m;
	size_t	ll;
	size_t	bl;

	ll = ft_strclen((const char *)*line, '\0');
	bl = ft_strclen((const char *)buf, c);
	newline = (char *)malloc(sizeof(char) * (ll + bl + 1));
	if (!newline)
		return ;
	m = newline;
	c = 0;
	while (ll)
	{
		*m++ = (*line)[c];
		--ll;
		++c;
	}
	while (bl)
	{
		*m++ = *(buf++);
		--bl;
	}
	*m = '\0';
	free(*line);
	*line = newline;
	return ;
}

/*
* Shifts the buffer from nl_pos + 1 until an '\0' is encountered to the start
* of buf. bzero out the remainder of buf. Returns the bytes shifted.
*/
size_t	ft_shift_buf(char *buf, char *nl_pos)
{
	size_t	bytes_shifted;

	bytes_shifted = 0;
	++nl_pos;
	while (nl_pos[bytes_shifted] != '\0')
		*(buf++) = nl_pos[bytes_shifted++];
	while (*(buf) != '\0')
		*(buf++) = '\0';
	return (bytes_shifted);
}
