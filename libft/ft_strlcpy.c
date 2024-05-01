/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:59:20 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 12:11:30 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (size == 0)
		return (j);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dst[i] != 0)
		dst[i] = '\0';
	return (j);
}

// int	main(void)
// {
// 	char dst[13] = "Gesu' Cristo";
// 	char src[] = "Isdfg";
// 	printf("Lunghezza %zu\n", ft_strlcpy(dst, src, 2));
// 	printf("%s", dst);
// 	return (0);
// }