/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:49:47 by nicolo            #+#    #+#             */
/*   Updated: 2023/10/26 19:10:59 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	num;
	int	neg;

	neg = 1;
	a = 0;
	num = 0;
	while (str[a] == 32 || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == 43)
		a++;
	else if (str[a] == 45)
	{
		neg = -1;
		a++;
	}
	while (str[a] <= 57 && str[a] >= 48)
	{
		num = (10 * num) + str[a] - 48;
		a++;
	}
	return (num * neg);
}

// int	main(void)
// {
// 	char a[50] = "";
// 	printf("%d", ft_atoi(a));
// }