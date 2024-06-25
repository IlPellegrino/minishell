/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:16:18 by nromito           #+#    #+#             */
/*   Updated: 2024/06/25 12:05:54 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_btrim(const char *str, const char *to_remove)
{
	char	*final_str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!str || !to_remove || !*str)
		return (0);
	final_str = ft_calloc(sizeof(char *), ft_strlen(str));
	if (!final_str)
		return (0);
	while (str[++i])
	{
		if (str[i] == to_remove[0] && str[i + 1] == to_remove[0])
			continue ;
		final_str[++j] = str[i];
	}
	return (final_str);
}
