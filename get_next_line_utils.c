/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:34:57 by prolling          #+#    #+#             */
/*   Updated: 2021/05/30 12:29:25 by prolling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* The  memchr()  function  scans  the  initial n bytes of the memory area
* pointed to by s for the first instance of c.  Both c and the bytes of the
* memory area pointed to by s are interpreted as unsigned char.
* The memchr() and memrchr() functions return a pointer to the matching byte
* or NULL if the character does not occur in the given memory area.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*m;

	m = (void *)s;
	while (n)
	{
		if (*(unsigned char *)m == (unsigned char)c)
			return (m);
		++m;
		--n;
	}
	return (0);
}

/*
* The memmove() function copies n bytes from memory area src to memory area
* dest. The memory areas may overlap: copying takes place as though the bytes in
* src are first copied into a temporary array that does not overlap src or dest,
* and the bytes are then copied from the temporary array to dest. The memmove()
* function returns a pointer to dest.
* memcpy if dest has enough space (dest-src >= n)
* otherwise a reverse write [dest <<< src] from position n to 0.
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if ((size_t)(dest - src) >= n)
		return (ft_memcpy(dest, src, n));
	while (n--)
		*((unsigned char *)dest + n) = *((unsigned char *)src + n);
	return (dest);
}

/*
* The  memcpy() function copies n bytes from memory area src to memory area
* dest. The memory areas must not overlap.  Use memmove(3) if the memory areas
* do overlap. The memcpy() function returns a pointer to dest.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*m;

	if (!dest && !src)
		return ((void *)0);
	m = dest;
	while (n)
	{
		*m = *(unsigned char *)src;
		++m;
		++src;
		--n;
	}
	return (dest);
}
