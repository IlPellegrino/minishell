/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <cristianiusca13@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:20:53 by ciusca            #+#    #+#             */
/*   Updated: 2023/10/24 21:02:51 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*arr;

	if (nitems != 0 && size > ULONG_MAX / nitems)
		return (NULL);
	arr = (void *)malloc(size * nitems);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, size * nitems);
	return (arr);
}
