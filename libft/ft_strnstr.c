/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:04:23 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 18:58:44 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	n;

	n = 0;
	i = 0;
	if (little[n] == '\0' || little == NULL)
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] && i < len)
	{
		while (big[i + n] == little[n] && big[i + n] && i + n < len)
			n++;
		if (n == ft_strlen(little))
			return ((char *)big + i);
		n = 0;
		i++;
	}
	return (NULL);
}
