/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:15 by noguen            #+#    #+#             */
/*   Updated: 2022/02/10 01:34:23 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send(int pid, unsigned char c)
{
	int		bin[8];
	int		i;

	i = -1;
	while (++i < 8)
	{
		if (c > 0)
			bin[i] = c % 2;
		else
			bin[i] = 0;
		c /= 2;
	}
	i = -1;
	while (++i < 8)
	{
		if (bin[7 - i] == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
	}
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "Server got message.\n", 20);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sig;
	long int			pid;
	int					i;

	if (argc != 3)
	{
		write(1, "Incorrect parameters.\n", 22);
	}
	sig.sa_handler = &handler;
	if (!ft_isnum(argv[1]))
	{
		return (0);
	}
	pid = ft_atoi(argv[1]);
	i = -1;
	sigaction(SIGUSR1, &sig, NULL);
	while (argv[2][++i])
		send(pid, argv[2][i]);
	while (1)
		pause();
	return (0);
}
