/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcekici <mcekici@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:44:23 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/11 17:56:57 by mcekici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void	ft_putstr(char *str);
static void	ft_putnbr(int nb);
static void	ft_putchar(char c);
static void	ft_create_char_by_bits(int sigval, siginfo_t *info, void *context);

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = ft_create_char_by_bits;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = getpid();
	ft_putstr("Server PID: ");
	ft_putnbr(pid);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

static void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

static void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar('-');
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_create_char_by_bits(int sigval, siginfo_t *info, void *context)
{
	static int	recived_count = 0;
	static char	c = 0;
	pid_t		client_pid;
	int			error;

	error = 0;
	client_pid = info->si_pid;
	(void)context;
	if (sigval == SIGUSR2)
		c |= 1 << (7 - recived_count);
	recived_count++;
	if (recived_count == 8)
	{
		if (c == '\0')
			ft_putstr("\n");
		else
			ft_putchar(c);
		recived_count = 0;
		c = 0;
	}
	error = kill(client_pid, SIGUSR1);
	if (error == -1)
		exit(EXIT_FAILURE);
}
