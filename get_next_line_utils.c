/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:57 by prolling          #+#    #+#             */
/*   Updated: 2021/06/05 20:04:16 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* The strchr() function returns a pointer to the first occurrence of the
* character c in the string s.
* RETURN: The  strchr()  and strrchr() functions return a pointer to the matched
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
	return (0);
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
