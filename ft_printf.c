#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		count;

	va_start(ap, fmt);
	i = 0;
	count = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			i++;
			count += handle_format(fmt[i], ap);
		}
		else if (fmt[i] == '%' && !fmt[i + 1])
		{
			va_end(ap);
			return (count);
		}
		else
			count += write(1, &fmt[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
