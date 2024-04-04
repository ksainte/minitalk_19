/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksainte <ksainte19@student.s19>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:50:53 by ksainte           #+#    #+#             */
/*   Updated: 2024/04/04 23:56:07 by ksainte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <signal.h>
#include <limits.h>

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

void	byte_reception(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("bit intercepted is 1\n");
	else
		ft_printf("bit intercepted is 0\n");
}

void	ft_check_args(int argc, char **argv, int *pid)
{
	size_t	i;

	if (argc != 3)
	{
		ft_printf("Wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (ft_isdigit(argv[1][i]) == 1)
		i++;
	*pid = ft_atoi(argv[1]);
	if (argv[1][i] != '\0' || *pid < 1 || *pid >= INT_MAX)
	{
		ft_printf("Invalid PID\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	pid_t		pid;
	const char	*string;
	int			i;

	signal(SIGUSR1, byte_reception);
	signal(SIGUSR2, byte_reception);
	ft_check_args(argc, argv, &pid);
	ft_printf("Sending bytes over the server...\n");
	string = argv[2];
	i = 0;
	while (string[i])
	{
		send_byte(pid, string[i]);
		if (i % 100 == 0)
			usleep(100);
		i++;
	}
	send_byte(pid, '\0');
	return (0);
}
