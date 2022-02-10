/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:26 by noguen            #+#    #+#             */
/*   Updated: 2022/02/10 17:51:34 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bin_to_char(int sigusr)
{
	static char	c = 0;
	static int	i = 8;

	if (sigusr == SIGUSR1)
		c |= (0 << --i);
	else if (sigusr == SIGUSR2)
		c |= (1 << --i);
	if (i == 0)
	{
		if (c == '\0')
			write(1, "\n", 1);
		write(1, &c, 1);
		i = 8;
		c = 0;
	}
}

void	handler(int sigusr)
{
	if (sigusr == SIGUSR1 || sigusr == SIGUSR2)
		bin_to_char(sigusr);
	else
		exit(0);
}

int	main(void)
{
	write(1, "PID => ", 7);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	if (signal(SIGUSR1, handler) == SIG_ERR)
	{
		write(1, "Sending error.\n", 15);
		exit(1);
	}
	if (signal(SIGUSR2, handler) == SIG_ERR)
	{
		write(1, "Sending error.\n", 15);
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
