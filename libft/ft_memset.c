/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:29:09 by marvin            #+#    #+#             */
/*   Updated: 2023/10/10 20:29:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*array;
	size_t			i;

	array = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		array[i] = c;
		i ++;
	}
	return (str);
}

/*int	main(void)
{
	char	str[13];
	char	str2[13];

	ft_memset(str, 'f', 10);
	memset(str2, 'f', 10);

	printf("mine %s\n", str);
	printf("real %s", str2);
}*/