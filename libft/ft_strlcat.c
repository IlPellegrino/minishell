/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:43:33 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 14:35:30 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (size == 0)
		return (ft_strlen(src));
	if (size < j)
		return (size + ft_strlen(src));
	while (src[i] != '\0' && i + j < size - 1)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + ft_strlen(src));
}

// int	main(void)
// {
// 	char dst[13] = "Gesu' Cristo";
// 	char src[] = "hfwjh";
// 	printf("La rivelazione e' che %zu\n", ft_strlcat(dst, "123", 0));
// 	printf("%s", dst);
// 	return (0);
// }