/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:15 by noguen            #+#    #+#             */
/*   Updated: 2022/02/09 00:34:09 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*char_to_bin(int c)
{
	int		bin[8];
	char	*binary;
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
	binary = malloc(sizeof(char) * 9);
	i = -1;
	while (++i < 8)
		binary[i] = bin[7 - i] + 48;
	binary[i] = '\0';
	return (binary);
}

void	str_to_bin(t_client *client, char *bin)
{
	int	i;

	i = -1;
	client->bin_msg = malloc(sizeof(char *) * (client->len + 2));
	while (++i < client->len + 2)
		client->bin_msg[i] = NULL;
	i = -1;
	while (bin[++i])
		client->bin_msg[i] = char_to_bin((int)bin[i]);
	client->bin_msg[i] = char_to_bin(0);
	client->bin_msg[i + 1] = NULL;
}

void	send_sig(t_client *client, int sigusr)
{
	int	tmp;

	if (sigusr == 1)
	{
		tmp = kill(client->pid, SIGUSR1);
		if (tmp == -1)
		{
			exit_client(client);
			write(1, "Can't send siganl.\n", 19);
			exit(0);
		}
	}
	else if (sigusr == 2)
	{
		tmp = kill(client->pid, SIGUSR2);
		if (tmp == -1)
		{
			write(1, "Can't send siganl.\n", 19);
			exit(0);
		}
	}
}

void	send_msg(t_client *client, char *msg)
{
	int	i;
	int	j;

	i = -1;
	str_to_bin(client, msg);
	while (client->bin_msg[++i])
	{
		j = - 1;
		usleep(30);
		while (++j < 8)
		{
			usleep(30);
			if (client->bin_msg[i][j] == '0')
				send_sig(client, 1);
			else if (client->bin_msg[i][j] == '1')
				send_sig(client, 2);
		}
	}
}


int	main(int argc, char *argv[])
{
	t_client	client;

	if (argc != 3)
	{
		write(1, "Incorrect parameters.\n", 22);
		exit_client(&client);
	}
	if (!ft_isnum(argv[1]))
	{
		write(1, "123", 3);
		return (0);
	}
	client.pid = ft_atoi(argv[1]);
	client.len = ft_strlen(argv[2]);
	send_msg(&client, argv[2]);
	exit_client(&client);
}
