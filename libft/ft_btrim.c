/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:16:18 by nromito           #+#    #+#             */
/*   Updated: 2024/06/21 18:55:40 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_btrim(const char *str, const char *to_remove)
{
	char	*newstr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	newstr = ft_calloc(sizeof(char *), ft_strlen(str));
	if (!newstr)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == to_remove[0])
			newstr[++j] = str[i++];
		while (str[i] && str[i] == to_remove[0])
			i++;
		while (str[i] && str[i] != to_remove[0])
			newstr[++j] = str[i++];
	}
	return (newstr);
}