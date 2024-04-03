/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte19@student.s19>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:51:06 by ksainte           #+#    #+#             */
/*   Updated: 2024/04/03 23:02:47 by ksainte          ###   ########.fr       */
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

void	signal_handler(int signal)
{
	static unsigned char	current_byte;
	unsigned char			c;
	static int				bit;

	c = define_bit(signal);
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
}

int	main(void)
{
	printf("%d\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
