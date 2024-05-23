/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:03:00 by ciusca            #+#    #+#             */
/*   Updated: 2024/02/17 19:04:18 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	len_n(unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_reverse(char *str, int i)
{
	int		j;
	char	temp;

	j = 0;
	while (j < (i / 2))
	{
		temp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = temp;
		j++;
	}
	return (str);
}

int	hexa_converter(unsigned int nb, int change)
{
	char	*hexnb;
	int		i;
	int		n;

	i = 0;
	if (nb == 0)
		return (write (1, "0", 1));
	hexnb = malloc(sizeof(char) * len_n(nb) + 1);
	if (!hexnb)
		return (0);
	while (nb > 0)
	{
		n = nb % 16;
		if (n < 10)
			hexnb[i] = n + '0';
		else
			hexnb[i] = n - 10 + pf_toupper('a', change);
		nb = nb / 16;
		i++;
	}
	hexnb = ft_reverse(hexnb, i);
	write (1, hexnb, i);
	free(hexnb);
	return (i);
}
