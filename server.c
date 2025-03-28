#include <signal.h>
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd);
void	signal_reciver(int signum);

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "pid: ", 5);
	ft_putnbr_fd(pid, 1);
	write(1, "\tListening SIGUSR1 & SIGUSR2..\n", 31);
	signal(SIGUSR1, signal_reciver);
	signal(SIGUSR2, signal_reciver);
	while (1)
		pause();
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (!(n <= 9 && n >= 0))
	{
		ft_putnbr_fd(n / 10, fd);
		write(fd, &("0123456789"[n % 10]), 1);
	}
	else
		write(fd, &("0123456789"[n % 10]), 1);
}

void	signal_reciver(int signum)
{
	static char	c = 0;
	static int	count = 0;

	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1;
	count ++;
	if (count == 8)
	{
		write(1, &c, 1);
		c = 0;
		count = 0;
	}
}