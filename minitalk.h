/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:00:33 by noguen            #+#    #+#             */
/*   Updated: 2022/02/10 18:07:56 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_client
{
	pid_t	pid;
	char	**bin_msg;
	int		len;
}				t_client;

size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_isnum(char *str);
void		ft_putnbr(int num);
void		exit_client(t_client *client);
void		error_client(void);

#endif
