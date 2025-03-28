#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static int		ft_atoi(const char *str);
void	send_bit(int pid, char bit);
void	send_message(int server_pid, char *message);

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		write(1, "Invalid arguments, try: ./client [pid] [message]\n", 49);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "Error: invalid pid!\n", 20);
		exit(EXIT_SUCCESS);
	}
	send_message(pid, argv[2]);
	return (0);
}

void	send_message(int server_pid, char *message)
{
	int	i;
	int	bit;

	while (*message)
	{
		i = 7;
		while (i >= 0)
		{
			bit = (*message >> i) & 1;
			send_bit(server_pid, bit);
			i--;
		}
		message++;
	}
}
void	send_bit(int pid, char bit)
{
	if (bit)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			write(1, "kill() error, program is closing..\n", 35);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			write(1, "kill() error, program is closing..\n", 35);
			exit(EXIT_FAILURE);
		}
	}
	usleep(500);
}

static int	ft_atoi(const char *str)
{
	int	sign;
	int	value;

	sign = 1;
	value = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str ++;
	}
	while (*str <= '9' && *str >= '0')
		value = value * 10 + (*str++ - '0');
	if (*str)
	{
		write(1, "Error: invalid pid!\n", 20);
		exit(EXIT_SUCCESS);
	}
	return (value * sign);
}
