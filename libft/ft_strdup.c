/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:40:06 by nromito           #+#    #+#             */
/*   Updated: 2023/10/26 19:22:49 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*st;
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	st = malloc(sizeof(char) * i + 1);
	if (!st)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		st[i] = s[i];
		i++;
	}
	st[i] = '\0';
	return (st);
}

// int main(void)
// {
//     const char *str1 = "Hello, World!";
//     const char *str2 = NULL;
//     const char *str3 ;
//     // Valid input
//     char *dup1 = ft_strdup(str1);
//     printf("Duplicate 1: %s\n", dup1);
//     free(dup1);
//     // Empty string
//     char *dup2 = ft_strdup(str2);
//     if (dup2 == NULL)
//     {
//         printf("Error: Empty string\n");
//     }
//     else
//     {
//         printf("Duplicate 2: %s\n", dup2);
//         free(dup2);
//     }
//     // Null pointer
//     char *dup3 = ft_strdup(str3);
//     // if (dup3 == NULL)
//     // {
//     //     printf("Error: Null pointer\n");
//     // }
//         printf("Duplicate 3: %s\n", dup3);
//         free(dup3);
//     return 0;
// }