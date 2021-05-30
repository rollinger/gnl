/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:57 by prolling          #+#    #+#             */
/*   Updated: 2021/05/30 11:40:55 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

/*
* Copies the buffer from start to \n/EOF into the line and memmoves the right
* portion to the start.
* returns length of fragment shifted
*/
size_t	copy_line_shift_fragment(fd, *buf, *line)
{
	while ()
	{

	}
}
