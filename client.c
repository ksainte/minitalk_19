/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte19@student.s19>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:48:57 by ksainte           #+#    #+#             */
/*   Updated: 2024/04/03 23:47:39 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <signal.h>

void	send_byte(int pid, unsigned char byte)
{
	int				i;
	unsigned char	temp_byte;

	temp_byte = byte;
	i = 8;
	while (i > 0)
	{
		i--;
		temp_byte = byte >> i;
		if (temp_byte % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(42);
	}
}

int	main(int argc, char *argv[])
{
	pid_t		pid;
	const char	*string;
	int			i;

	if (argc != 3)
	{
		ft_printf("Wrong number of arguments\n");
		exit(0);
	}
	pid = ft_atoi(argv[1]);
	string = argv[2];
	i = 0;
	while (string[i])
	{
		send_byte(pid, string[i]);
		i++;
	}
	send_byte(pid, '\0');
	return (0);
}
