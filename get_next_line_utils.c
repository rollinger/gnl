/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:57 by prolling          #+#    #+#             */
/*   Updated: 2021/06/10 07:12:06 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* The strchr() function returns a pointer to the first occurrence of the
* character c in the string s.
* RETURN: The  strchr() functions return a pointer to the matched
* character or NULL if the character is not found. The terminating null byte is
* considered part of the string, so that if c is specified as '\0', these
* functions return a pointer to the terminator.
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
* The  bzero() function erases the data in the n bytes of the memory starting
* at the location pointed to by s, by writing zeros (bytes containing '\0')
* to that area. It returns void.
*/
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*m;

	m = s;
	while (n--)
		*(m++) = '\0';
	return ;
}

/*
* Extended strlen that returns if c is found or \0
*/
size_t	ft_strclen(const char *s, char c)
{
	size_t	int_len;

	int_len = 0;
	while (s[int_len] != '\0' && s[int_len] != c)
		int_len++;
	return (int_len);
}

/*
* The calloc() function allocates memory for an array of nmemb elements of size
* bytes each and returns a pointer to the allocated memory. The memory is set
* to zero. If nmemb or size is 0, then calloc() returns either NULL, or a
* unique pointer value that can later be successfully passed to free().
* size_t: unsigned int (kind of guaranteed to hold array indexes)
* BUG: if nmemb*size > size_t then should return error.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*arr;
	unsigned char	*m;
	size_t			bytes;

	bytes = nmemb * size;
	arr = malloc(bytes);
	if (bytes && arr)
	{
		m = arr;
		if (arr)
			while (bytes--)
				*(m++) = '\0';
	}
	return (arr);
}
