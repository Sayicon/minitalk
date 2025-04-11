/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcekici <mcekici@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:44:13 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/11 17:55:56 by mcekici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int	g_signal_flag = 0;

static void	ft_send_char_bits(char c, int pid);
static int	ft_atoi_mod(const char *str);
static void	ft_server_affirmation(int sigval);
static void	ft_failure_processor(int option);

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc != 3)
		ft_failure_processor(1);
	if (argc == 3)
	{
		pid = ft_atoi_mod(argv[1]);
		if (pid <= 0)
			ft_failure_processor(2);
		signal(SIGUSR1, ft_server_affirmation);
		while (argv[2][i])
			ft_send_char_bits(argv[2][i++], pid);
		ft_send_char_bits('\0', pid);
		write(1, "Message sended.\n", 13);
	}
	exit (EXIT_SUCCESS);
}

static int	ft_atoi_mod(const char *str)
{
	int	i;
	int	strg;
	int	j;

	j = 0;
	strg = 0;
	i = 0;
	while (str[i] == '+')
	{
		i++;
		if (i > 1)
			ft_failure_processor(2);
	}
	while (str[i + j])
	{
		if (!(str[i + j] >= '0' && str[i + j] <= '9'))
			ft_failure_processor(2);
		j++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		strg = (10 * strg) + (str[i] - '0');
		i++;
	}
	return (strg);
}

static void	ft_send_char_bits(char c, int pid)
{
	int	i;
	int	error;

	error = 0;
	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			error = kill(pid, SIGUSR2);
		else
			error = kill(pid, SIGUSR1);
		if (error == -1)
			ft_failure_processor(3);
		i--;
		while (!g_signal_flag)
			pause();
		g_signal_flag = 0;
	}
}

static void	ft_failure_processor(int option)
{
	if (option == 1)
		write(2, "Error! Usage: <PID> <MESSAGE>\n", 30);
	else if (option == 2)
	{
		write(2, "Error (PID is incorrect)\n", 25);
		write(2, "PID must be a positive number.\n", 31);
	}
	else if (option == 3)
	{
		write(2, "Error kill()\n", 13);
	}
	exit(EXIT_FAILURE);
}

static void	ft_server_affirmation(int sigval)
{
	if (sigval == SIGUSR1)
		g_signal_flag = 1;
}
