#include "ft_printf.h"

static int num_len(long n)
{
	int len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int print_nbr(int n)
{
	char buffer[32];
	long nb;
	int len;
	int i;

	nb = n;
	len = num_len(nb);
	i = len - 1;

	if (nb == 0)
		buffer[0] = '0';
	else
	{
		if (nb < 0)
		{
			buffer[0] = '-';
			nb = -nb;
		}
		while (nb > 0)
		{
			buffer[i] = '0' + (nb % 10);
			nb /= 10;
			i--;
		}
	}
	return (write(1, buffer, len));
}