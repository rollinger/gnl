/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:39 by prolling          #+#    #+#             */
/*   Updated: 2021/06/07 08:33:00 by prolling         ###   ########.fr       */
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
* MAX_FD: max number of file descriptors. defined by the system. default 1024
* BUFFER_SIZE: optimal buffer size - set by OS/Compilation. Often 4096 bytes
*
* Algorithm:
* GOAL: Read one line at a time from fd to line. (buf must hold state of n FDs
* between gnl calls)
*	1) pre function sanity checks: return (-1)
*	2) append, shift & reload buf to *line until a \n is found in buf[fd]
*	3) append newline protion of buf[fd] to *line, shift and reload buffer
*	4) return (0) if buf starts with \0 otherwise \n
*	Buffer State is persistent because of static fd_buf var.
* 	- Return (1) if \n\0 string is in line.
* 	- Return (0) if fd has encountered EOF (buf starts with a \0)
* 	- Return (-1) on error
*/
int	get_next_line(int fd, char **line)
{
	static char	fd_buf[MAX_FD][BUFFER_SIZE + 1];
	char		*nl_pos;
	size_t		shifted;

	*line = (char *)calloc(sizeof(char), 1);
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
	ft_reload_buf(fd, fd_buf[fd], shifted, BUFFER_SIZE + 1);
	if (fd_buf[fd][0] == '\0')
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
* Reloads the <buf> at <fd> via the read() call from start to end - 1 into the
* buf. Last byte of any fd_buf is a \0.
* Returns the number of bytes read; 0 if EOF from the read()
*/
int	ft_reload_buf(int fd, char *buf, size_t start, size_t end)
{
	int	nb_read;

	nb_read = read(fd, (void *)&buf[start], end - start - 1);
	return (nb_read);
}

/*
* Appends the <buf> until <c> is encountered to the end of <*line> making a
* bigger newline that holds old <*line> and new <buf> content and replacing
* the <**line>, freeing the old <*line>.
* newline length is old_line_length + buf_to_c_length +1 for \0 term. newline
* is calloc'ed so \0 is there.
*/
void	ft_append_buf_line(char **line, char *buf, int c)
{
	char	*newline;
	char	*m;
	size_t	ll;
	size_t	bl;

	ll = ft_strclen((const char *)*line, '\0');
	bl = ft_strclen((const char *)buf, c);
	newline = (char *)calloc(sizeof(char), (ll + bl + 1));
	if (!newline)
		return ;
	m = newline;
	c = 0;
	while (ll)
	{
		*m++ = (*line)[c++];
		--ll;
	}
	while (bl)
	{
		*m++ = *(buf++);
		--bl;
	}
	free(*line);
	(*line) = newline;
	return ;
}

/*
* Shifts the buffer from nl_pos + 1 until an '\0' is encountered to the start
* of buf. nl_pos is incremented once before operation, because nl_pos is on
* the \n char. After shifting the remainder of buf is bzero'ed out.
* Returns the bytes shifted.
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
