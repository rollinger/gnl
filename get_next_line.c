/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:39 by prolling          #+#    #+#             */
/*   Updated: 2021/05/30 11:40:49 by prolling         ###   ########.fr       */
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
