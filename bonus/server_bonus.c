/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:22:50 by bchafi            #+#    #+#             */
/*   Updated: 2025/02/28 10:47:55 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_cpid = 0;

int	expected(int expected_bytes, int accumulator, int buff_i)
{
	if (buff_i == 1)
	{
		if ((accumulator > 128) == 0)
			expected_bytes = 1;
		else if ((accumulator & 0b11100000) == 0b11000000)
			expected_bytes = 2;
		else if ((accumulator & 0b11110000) == 0b11100000)
			expected_bytes = 3;
		else if ((accumulator & 0b11111000) == 0b11110000)
			expected_bytes = 4;
		else
		{
			buff_i = 0;
			expected_bytes = 1;
		}
	}
	return (expected_bytes);
}

void	check(unsigned char *add, int *b_count, int *buff_i, siginfo_t *info)
{
	if (g_cpid != info->si_pid)
	{
		(*add) = 0;
		(*b_count) = 0;
		(*buff_i) = 0;
		g_cpid = info->si_pid;
	}
}

void	sig_usr(int sig, siginfo_t *info, void *context)
{
	static unsigned char	add;
	static unsigned char	buffer[4];
	static int				b_count;
	static int				expected_bytes = 1;
	static int				buff_i;

	(void)context;
	check(&add, &b_count, &buff_i, info);
	add = add << 1;
	if (sig == SIGUSR2)
		add |= 1;
	b_count++;
	if (b_count == 8)
	{
		buffer[buff_i++] = add;
		expected_bytes = expected(expected_bytes, add, buff_i);
		if (buff_i == expected_bytes)
		{
			write(1, buffer, expected_bytes);
			(1) && (buff_i = 0, expected_bytes = 1);
		}
		if (add == '\0')
			(1) && (ft_printf("\n"), kill(g_cpid, SIGUSR1));
		b_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = sig_usr;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
		pause();
}
