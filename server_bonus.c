/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte19@student.s19>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:50:58 by ksainte           #+#    #+#             */
/*   Updated: 2024/04/03 23:29:59 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <signal.h>

#define TERMINATE_COMMUNICATION '\0'

int	define_bit(int signal)
{
	if (signal == SIGUSR1)
		return (1);
	else
		return (0);
}

void	handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	current_byte;
	unsigned char			c;
	static int				bit;

	(void)context;
	c = define_bit(signo);
	current_byte |= c;
	bit++;
	if (bit == 8)
	{
		if (current_byte == TERMINATE_COMMUNICATION)
			ft_printf("\n");
		else
			ft_printf("%c", current_byte);
		bit = 0;
		current_byte = 0;
	}
	else
		current_byte = current_byte << 1;
	if (signo == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handler;
	ft_printf("%d\n", getpid());
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
