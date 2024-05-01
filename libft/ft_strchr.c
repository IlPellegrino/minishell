/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:03:04 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 13:57:27 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	j;

	j = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == j)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == j)
		return ((char *)s + i);
	return (0);
}
