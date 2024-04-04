/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte19@student.s19>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:51:06 by ksainte           #+#    #+#             */
/*   Updated: 2024/04/04 19:58:51 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <signal.h>

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
		if (current_byte == '\0')
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
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		usleep(300);
	return (0);
}
