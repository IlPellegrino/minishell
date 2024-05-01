/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:43:40 by nromito           #+#    #+#             */
/*   Updated: 2023/10/29 09:39:36 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		join = malloc(sizeof(char) * (len1 + len2 + 1));
		if (join == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			join[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			join[len1] = s2[i];
			len1++;
		}
		join[len1] = '\0';
		return (join);
	}
	return (NULL);
}

// int main(void)
// {
//     const char *s1 = "Hello, ";
//     const char *s2 = "world!";
//     char *result = ft_strjoin(s1, s2);
//     printf("Joined string: %s\n", result);
//     free(result);
//     return 0;
// }