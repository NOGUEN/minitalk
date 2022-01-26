/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:26 by noguen            #+#    #+#             */
/*   Updated: 2022/01/26 22:27:54 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signo, siginfo_t *info, void *context)
{
	if (signo == SIGUSR1)
		write(1, "1", 1);
	else if (signo == SIGUSR2)
		write(1, "0", 1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) != 0)
	{
		printf("sigaction error");
		exit(1);
	}
	if (sigaction(SIGUSR2, &act, NULL) != 0)
	{
		printf("sigaction error");
		exit(1);
	}
	while (1)
		;
	return (0);
}
