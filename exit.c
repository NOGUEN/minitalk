/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:53:22 by noguen            #+#    #+#             */
/*   Updated: 2022/02/07 14:22:59 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_client(t_client *client)
{
	int	i;

	i = -1;
	while (++i < client->len)
	{
		if (!client->bin_msg[i])
		{
			free(client->bin_msg[i]);
			client->bin_msg[i] = NULL;
		}
	}
	if (client->bin_msg)
		free(client->bin_msg);
	exit(0);
}
