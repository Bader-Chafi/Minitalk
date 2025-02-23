/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:11:55 by bchafi            #+#    #+#             */
/*   Updated: 2025/02/22 20:40:51 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_server_id;

void	fail_kill(int n)
{
	if (n == -1)
		exit(EXIT_FAILURE);
	return ;
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
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	fail;

	i = 0;
	fail = 0;
	if (ac != 3)
	{
		ft_printf("**the argument are not valid !!**");
		exit(EXIT_FAILURE);
	}
	g_server_id = ft_atoi(av[1]);
	if (g_server_id < 0 || g_server_id > PID_MAX)
	{
		ft_printf("**the PID are not valid !!**");
		exit(EXIT_FAILURE);
	}
	while (av[2][i])
		convert_to_bits(av[2][i++], g_server_id);
	convert_to_bits('\0', g_server_id);
	return (0);
}
