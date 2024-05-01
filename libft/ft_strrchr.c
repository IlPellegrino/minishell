/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:13:41 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 16:48:46 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	j;

	j = (unsigned char)c;
	i = ft_strlen(s);
	i -= 1;
	if (s == NULL)
		return (NULL);
	if (s[i + 1] == j)
		return ((char *)&s[i + 1]);
	while (i >= 0)
	{
		if (s[i] == j)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == j)
		return ((char *)s + i);
	return (0);
}

// int main(void)
// {
//     const char *str = "Hello, World!";
//     // int search_char = 0;
//     char *result = ft_strrchr(str, '\0');
//     printf("Result: %s\n", result);
//     return 0;
// }