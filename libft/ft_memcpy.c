/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:21:02 by marvin            #+#    #+#             */
/*   Updated: 2023/10/10 21:21:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destination;
	char	*source;

	if (!dest && !src)
		return (0);
	destination = (char *)dest;
	source = (char *)src;
	while (n-- > 0)
		destination[n] = source[n];
	return (destination);
}

/*
{
	char src[] = "test basic du memcpy !";
	char buff1[22];
	char *r2 = ft_memcpy(buff1, src, 22);

	printf("%s", buff1);
}*/