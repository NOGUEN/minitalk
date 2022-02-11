/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:26 by noguen            #+#    #+#             */
/*   Updated: 2022/02/11 21:23:16 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	convert(int *c, int *i, int sigusr)
{
	if (sigusr == SIGUSR1)
		(*c) |= (1 << --(*i));
	else if (sigusr == SIGUSR2)
		(*c) |= (0 << --(*i));
}

void	get_size(int *c, int *cnt, int flag)
{
	static int	t = 0;

	if (flag == 0)
		t += (*c);
	else if (flag == 1)
		(*cnt) = t;
	else
		t = 0;
}

void	init(int *i, int *c, int *cnt, int flag)
{
	if (flag == 0)
	{
		if (*c != 0)
			get_size(c, cnt, 0);
		else
			get_size(c, cnt, 1);
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
		get_size(c, cnt, 2);
		write(1, "\n", 1);
	}
}

void	encode(int sigusr, siginfo_t *info, void *tmp)
{
	static int	c = 0;
	static int	i = 8;
	static int	cnt = -1;
	char		g;

	(void)tmp;
	convert(&c, &i, sigusr);
	if (i == 0)
	{
		if (cnt == -1)
			init(&i, &c, &cnt, 0);
		else
		{
			g = (char)c;
			write(1, &g, 1);
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
	while (1)
		pause();
	return (0);
}
