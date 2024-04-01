/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudin <lgaudin@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:02:14 by lgaudin           #+#    #+#             */
/*   Updated: 2023/06/10 14:29:08 by lgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>


void	send_byte(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_byte;

	
	// i = 7;
	// character = 97;
	temp_byte = character;
	// printf("%d\n", temp_char);
	// for (int i = 7; i >= 0; i--) {
    //     printf("%d", (temp_char >> i) & 1);
    // }
	i = 7;
	while (i >= 0)
	{
		temp_byte = character >> i;
		if (temp_byte % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(42);
		i--;
	}
}


// int	main(int argc, char *argv[])
int	main()
{
	pid_t		pid;
	const char	*string;
	int			i;

	// if (argc != 3)
	// {
	// 	ft_printf("Usage: %s <pid> <message>\n", argv[0]);
	// 	exit(0);
	// }
	// pid = ft_atoi(argv[1]);
	// string = argv[2];
	pid = 43581;
	string = "alklsdjlkjfsdkljfkjksdjkjlkjslkdjkfjkdjlskjdlkjlskj";
	i = 0;
	while (string[i]){
		send_byte(pid, string[i]);
		i++;
	}
	send_byte(pid, '\0');
	return (0);
}
