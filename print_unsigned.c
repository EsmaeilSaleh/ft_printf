#include "ft_printf.h"

static int	un_len(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	print_unsigned(unsigned int n)
{
	char	buffer[32];
	int		len;
	int		i;

	len = un_len(n);
	i = len - 1;
	while (i >= 0)
	{
		buffer[i] = '0' + (n % 10);
		n /= 10;
		i--;
	}
	return (write(1, buffer, len));
}
