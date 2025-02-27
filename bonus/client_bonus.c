/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:32:16 by bchafi            #+#    #+#             */
/*   Updated: 2025/02/27 20:10:49 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	fail_kill(int n)
{
	if (n == -1)
		exit(EXIT_FAILURE);
}

void	ack(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message sent\n");
}

void	convert_to_bits(char s, int id_server)
{
	int	i;
	int	fail;

	i = 7;
	fail = 0;
	while (i >= 0)
	{
		if ((s >> i) & 1)
			fail = kill(id_server, SIGUSR2);
		else
			fail = kill(id_server, SIGUSR1);
		fail_kill(fail);
		i--;
		usleep(200);
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	fail;
	int	pid;

	i = 0;
	fail = 0;
	if (ac != 3)
	{
		ft_printf("**the argument are not valid !!**");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(av[1]);
	if (pid < 0 || pid > PID_MAX)
	{
		ft_printf("**the PID are not valid !!**");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, ack);
	while (av[2][i])
		convert_to_bits(av[2][i++], pid);
	convert_to_bits('\0', pid);
	return (0);
}
