/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:39 by prolling          #+#    #+#             */
/*   Updated: 2021/05/30 12:30:04 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* Write a function which returns a line read from a file descriptor, without
* the newline
* Parameter
* #1. file descriptor for reading
* #2. The value of what has been read
* Returns:
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
		- If no \n/EOF is in buf, read (BUFFER_SIZE - fragment_length) bytes
* 		to buf start appending it to buf content.
* 	- Return (1) if \n\0 string is in line.
* 	- Return (0) if fd has encountered EOF
* 	- Return (-1) on error
*/
int	get_next_line(int fd, char **line)
{
	static char	fd_buffer[MAX_FD][BUFFER_SIZE + 1];
	int			buf_state;

	if (!valid_fd(fd) || BUFFER_SIZE <= 0)
		return (-1);
	buf_state = 1;
	// buffer update loop until nl found or error (0/-1)
	while (buf_state > 0)
	{
		// cache full buffer and/or fill buffer up by reading remaining bytes
		buf_state = get_buffer_state(&fd_buffer[fd]);
	}
	if (buf_state == 0)
	{
		copy_line_shift_fragment(&fd_buffer[fd], *line)
		return (1);
	}
}

/*
* Valid file descriptors must be positive and not exceed the MAX_FD definition
*/
size_t	valid_fd(int fd)
{
	if (fd < 0 || fd > MAX_FD)
		return (0);
	else
		return (1);
}

/*
* Returns in which state the buffer is at fd
* Returns (-1) on error; (0) if buf contains a newline; (>0) pos until which
* content is present without a newline.
* If return == BUFFER_SIZE + 1 the buffer is full and has no \n.
* return >0 indicates a buffer update operation is needed to fill up the buffer
* return 0 indicates copy and shift operation is needed
*/
int	get_buffer_state(char *buf)
{
	int	state;

	if (!buf)
		return (-1);
	state = 0;
	while (buf[state] != '\0')
	{
		if (buf[state] == '\n')
			return (0);
		++state;
	}
	return (state);
}

/*
* Copies the buffer from start to \n into the line and memmoves the remaining
* right hand portion to the start of the buffer. The line contains the \n (!)
* returns length of fragment shifted
*/
size_t	copy_line_shift_fragment(char *buf, char *line)
{
	char 	*newline;
	size_t	length;

	newline = (char *)ft_memchr((const void *)buf, '\n', BUFFER_SIZE + 1);
	length = newline - buf + 1;
	ft_memcpy((void *)line, (const void *)buf, length);
	ft_memmove((void *)buf, (const void *)newline, BUFFER_SIZE - length);
	return (length);
}

/*
* Updates the buffer at fd from a read() call with max (BUFFER_SIZE - frag_start
* + 1) of content appending at position frag_start.
* to the fragment.
* nbytes = BUFFER_SIZE - fragment_length + 1
* fragment = string without terminating \n or EOF
* Returns (0) if EOF was encountered, (-1) on error or (nb_read)
*
*/
int	update_buffer_content(fd, buf, frag_start=0)
{
	int nb_read; //Check return vaue of read()

	nb_read = read(fd, &fd_read_buf[fd][f_start], BUFFER_SIZE - f_start + 1);
	return(nb_read)
}
