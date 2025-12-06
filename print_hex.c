#include "ft_printf.h"

static int hex_len(unsigned long n)
{
	int len;

	len = 1;
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int print_hex(unsigned long n, int upper)
{
	char buffer[32];
	for (int j = 0; j < 32; j++)
		buffer[j] = 0;
	char *base;
	int len;
	int i;

	base = upper ? "0123456789ABCDEF" : "0123456789abcdef";
	len = hex_len(n);
	i = len - 1;

	if (n == 0)
		buffer[0] = '0';
	else
	{
		while (n > 0)
		{
			buffer[i] = base[n % 16];
			n /= 16;
			i--;
		}
	}

	return (write(1, buffer, len));
}