/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:39:01 by nromito           #+#    #+#             */
/*   Updated: 2023/11/10 15:39:04 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	long	i;

	i = n;
	if (i < 0)
	{
		i = -i;
		write(fd, "-", 1);
	}
	digit = 48 + (i % 10);
	if (i >= 10)
		ft_putnbr_fd(i / 10, fd);
	write(fd, &digit, 1);
}

// int	main(void)
// {
// 	ft_putnbr_fd(965, 1);
// }