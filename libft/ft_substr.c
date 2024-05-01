/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:05:06 by nromito           #+#    #+#             */
/*   Updated: 2023/10/29 11:16:09 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int idx, size_t len)
{
	char	*sub;
	size_t	i;

	i = -1;
	if (idx > ft_strlen(s))
	{
		sub = malloc(sizeof(char) * 1);
		if (sub == NULL)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	s += idx;
	if (ft_strlen(s) <= len)
		sub = malloc(sizeof(char) * ft_strlen(s) + 1);
	else
		sub = malloc(sizeof(char) * len + 1);
	if (sub == NULL)
		return (NULL);
	while (s[++i] && i < len)
		sub[i] = s[i];
	sub[i] = '\0';
	return (sub);
}
/*
int	main(void)
{
 	char s1[] = "ciao sono io mi chiamo gianni";
 	char *f = ft_substr(s1, 0, 20);
 	printf("La sotto stringa e': %s\n", f);
	free(f);
	return (0);
}*/
