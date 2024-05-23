/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:49:06 by ciusca            #+#    #+#             */
/*   Updated: 2023/10/10 21:49:06 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	if (dest_ptr == src_ptr)
		return (dest);
	if (src_ptr < dest_ptr)
	{
		i = n + 1;
		while (--i > 0)
			dest_ptr[i - 1] = src_ptr[i - 1];
	}
	else
	{
		i = -1;
		while (++i < n)
			dest_ptr[i] = src_ptr[i];
	}
	return (dest);
}

/*int main(void)
{
	int 	size = 128 * 1024 * 1024;
	char *dst = (char *)malloc(sizeof(char) * size);
	char *data = (char *)malloc(sizeof(char) * size);

	ft_memmove(dst, data, size);
	printf("%s",dst);
}*/