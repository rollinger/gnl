/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:39 by prolling          #+#    #+#             */
/*   Updated: 2021/06/03 12:04:54 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* Write a function which returns a line read from a file descriptor, without
* the newline
* Parameter
* #1. file descriptor for reading
* #2. The value of what has been read
* Function Returns:
* 1 : A line has been read
* 0 : EOF has been reached
* -1 : An error happened
*
* fd_buffer => idx=FD [MAX_FD][BUFFER_SIZE + \0]
* buf_state => -1 undefined, 0 nl found, >0 pos until which the buffer is full
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
	static char	fd_buffer[MAX_FD][BUFFER_SIZE];
	int			buf_state[2];
	int			eof;
	size_t		line_size;

	if (!valid_fd(fd) || BUFFER_SIZE <= 0) //Maybe test malloc line too?
		return (-1);
	line_size = 0;
	buf_state = get_buffer_state(fd_buffer[fd]); //initial buffer state determ
	while (buf_state[1] != 1) // buffer update loop until nl found
	{
		// cache full buffer and/or fill buffer up by reading remaining bytes
		eof = update_buffer_content(fd, fd_buffer[fd], buf_state);
		if (eof == 0)
			break ;
		buf_state = get_buffer_state(fd_buffer[fd]);
		if (buf_state[1] == 1)
			break ;
		// Fully loaded w/o nl: cache all and
		copy_line_shift_fragment(fd_buffer[fd], *line);
		buf_state = get_buffer_state(fd_buffer[fd]);
	}
	if (buf_state == 1) // newline found
	{
		copy_line_shift_fragment(fd_buffer[fd], *line);
		return (1);
	}
	return (0); // has to handle EOF
}

/*
* Valid file descriptors must be positive and not exceed the MAX_FD definition
* return 0: not valid FD
* return 1: valid FD
*/
size_t	valid_fd(int fd)
{
	if (fd < 0 || fd > MAX_FD)
		return (0);
	else
		return (1);
}

/*
* Returns in which state the buffer is at the first state position.
* Returns [pos,0] if a \0 is found
* Returns [pos,1] if a \n is found
* pos: until which content is present without a newline.
* state: [0]=> counter [1]=>state (end-of-buffer / newline)
*/
int	*get_buffer_state(char *buf)
{
	int	state[2];

	state = {0, 0};
	while (state[0] < BUFFER_SIZE) //iterate BUFFER_SIZE-1 positions (0-idx)
	{
		if (buf[state[0]] == '\n')
		{
			state[1] = 1; //Newline found
			return (state);
		}
		if (buf[state[0]] == '\0')
		{
			state[1] = 0; //End of Buffer
			return (state);
		}
		++state[0];
	}
	return (state);
}

/*
* Copies the buffer from start to first \n -or- \0 into the *line and memmoves
* the remaining right hand portion to the start of the buffer.
* returns length of fragment shifted (remaining fragment)
*/
size_t	copy_line_shift_fragment(char *buf, char *line, int *buf_state)
{
	char	*frag_start;
	size_t	frag_length;

	frag_start = (buf + buf_state[0] + 1);
	frag_length = BUFFER_SIZE - buf_state[0];
	if (buf_state[0] > 0)
	{
		ft_memcpy((void *)line, (const void *)buf, buf_state[0]);
		ft_memmove((void *)buf, (const void *)frag_start, frag_length);
	}
	return (frag_start);
}

/*
* Updates the buffer at fd from a read() call with max (BUFFER_SIZE - frag_start
* + 1) of content appending at position frag_start.
* to the fragment.
* nbytes = BUFFER_SIZE - fragment_length + 1
* fragment = position at which the buffer was filled up to.
* Returns (0) if EOF was encountered, (-1) on error or (nb_read)
*/
int	update_buffer_content(int fd, char *buf, int *buf_state)
{
	int	nb_read;

	nb_read = read(fd, buf[buf_state[0]], BUFFER_SIZE - buf_state[0]);
	if (nb_read == 0)
		buf[buf_state[0]] = '\0'; //EOF at end of buffer
	return (nb_read);
}
