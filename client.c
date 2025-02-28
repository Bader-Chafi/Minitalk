/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:11:55 by bchafi            #+#    #+#             */
/*   Updated: 2025/02/28 10:20:30 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		usleep(200);
	}
}

int	parcing(char *s1, char *s2, int ac)
{
	int	pid;

	if (!s1 || !s2)
	{
		ft_printf("**the argument is empty!!**\n");
		exit(EXIT_FAILURE);
	}
	if (ac != 3)
	{
		ft_printf("**You must 3 arguments (executed file, pid, message)**\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(s1);
	if (pid <= 0 || pid > PID_MAX)
	{
		ft_printf("**the PID is not valid!!**\n");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	main(int ac, char **av)
{
	int	i;
	int	fail;
	int	pid;

	i = 0;
	fail = 0;
	pid = parcing(av[1], av[2], ac);
	if (av[2][i] != '\0')
	{
		while (av[2][i])
			convert_to_bits(av[2][i++], pid);
		convert_to_bits('\0', pid);
	}
	return (0);
}
