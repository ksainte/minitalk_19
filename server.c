/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:02:13 by lgaudin           #+#    #+#             */
/*   Updated: 2023/06/10 14:29:40 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define TERMINATE_COMMUNICATION '\0'



int define_bit(int signal){

	if (signal == SIGUSR1)
		return (1);
	else
		return(0);
}


void	signal_handler(int signal)
{
	static unsigned char	current_byte;
	unsigned char			c;
	static int				bit;//default value is 0

	c = define_bit(signal);
	//bitwise OR operation:
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

//Compile and run the program in one of the terminals. The program should block waiting for any signal. 
int	main(void)
{
	//Signal = un mécanisme de communication inter-processus
	printf("%d\n", getpid());
	//When a signal is received, the signal_handler function is called with the corresponding signal as an argument.
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1){
		pause();
	}
	return (0);
}
