/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:23:40 by bchafi            #+#    #+#             */
/*   Updated: 2025/02/23 11:47:02 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define PID_MAX 99999

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>
# include "../ft_printf/ft_printf.h"


int	ft_atoi(const char *str);
void sig_usr(int sig, siginfo_t *info, void *context);
void fail_kill(int n);
void ack(int sig);
void convert_to_bits(char s, int id_server);

#endif