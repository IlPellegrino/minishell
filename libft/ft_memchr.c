/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:01:31 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 18:24:27 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*g;
	unsigned char	j;

	j = (unsigned char)c;
	g = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (0);
	while (g[i] != j && i < n -1)
	{
		if (g[i] == j)
			return (g + i);
		i++;
	}
	if (g[i] == j)
		return (g + i);
	return (0);
}
