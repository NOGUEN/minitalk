/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:15 by noguen            #+#    #+#             */
/*   Updated: 2022/02/11 15:57:10 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

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
		usleep(30);
	}
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "Server got message.\n", 20);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sig;
	long int			pid;
	int					i;
	int					len;

	if (argc != 3)
		error_client();
	sig.sa_handler = &handler;
	if (!ft_isnum(argv[1]))
		error_client();
	len = ft_strlen(argv[2]);
	pid = ft_atoi(argv[1]);
	i = -1;
	sigaction(SIGUSR1, &sig, NULL);
	send(pid, len);
	while (argv[2][++i])
		send(pid, argv[2][i]);
	while (1)
		pause();
}
