/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:30 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 11:41:18 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	s = (const char *)src;
	d = (char *)dest;
	i = -1;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (++i < n)
		d[i] = s[i];
	return (dest);
}

// int main(void)
// {
// 	char s[] = "ciao\0ciao";
// 	char d[] = "";
// 	ft_memcpy(d, s, 10);
// 	for (int i = 0; i < 10; i++)
// 		printf("%c\t", d[i]);
// }