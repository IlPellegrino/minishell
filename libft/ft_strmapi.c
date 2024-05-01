/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:40:11 by nromito           #+#    #+#             */
/*   Updated: 2023/11/10 15:40:13 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ms;

	i = 0;
	ms = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ms == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		ms[i] = f(i, s[i]);
		i++;
	}
	ms[i] = '\0';
	return (ms);
}

// char mapping_function(unsigned int index, char c)
// {
//     /* Add 1 to the character's ASCII value */
//     return c - 32;
// }
// int main()
// {
//     char *input_string = "helloworld";
//     char *mapped_string = ft_strmapi(input_string, mapping_function);
//     if (mapped_string != NULL)
//     {
//         printf("Input string: %s\n", input_string);
//         printf("Mapped string: %s\n", mapped_string);
//         /* Remember to free the allocated memory */
//         free(mapped_string);
//     }
//     else
//     {
//         printf("Memory allocation failed.\n");
//     }
//     return 0;
// }