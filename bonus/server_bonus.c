/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:26 by noguen            #+#    #+#             */
/*   Updated: 2022/02/11 16:19:05 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

/*
void	get_size(int *i, char *c, int *cnt)
{

}*/

void	init(int *i, char *c, int *cnt, int flag)
{
	if (flag == 0)
	{
		*cnt = *c;
		*i = 8;
		*c = 0;
	}
	else if (flag == 1)
	{
		*i = 8;
		*c = 0;
		(*cnt)--;
	}
	else
	{
		(*cnt) = -1;
		write(1, "\n", 1);
	}
}

void	encode(int sigusr, siginfo_t *info, void *tmp)
{
	static char	c = 0;
	static int	i = 8;
	static int	cnt = -1;

	(void)tmp;
	if (sigusr == SIGUSR1)
		c |= (1 << --i);
	else if (sigusr == SIGUSR2)
		c |= (0 << --i);
	if (i == 0)
	{
		if (cnt == -1)
			init(&i, &c, &cnt, 0);
		else
		{
			write(1, &c, 1);
			init(&i, &c, &cnt, 1);
			if (cnt == 0)
			{
				kill(info->si_pid, SIGUSR1);
				init(&i, &c, &cnt, 2);
			}
		}
	}
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = &encode;
	write(1, "PID => ", 7);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while(1)
		pause();
	return (0);
}
