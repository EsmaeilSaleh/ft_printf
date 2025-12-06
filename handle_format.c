#include "ft_printf.h"

int	handle_format(char c, va_list ap)
{
	if (c == 'c')
		return (print_char(va_arg(ap, int)));
	if (c == 's')
		return (print_str(va_arg(ap, char *)));
	if (c == 'p')
		return (print_ptr(va_arg(ap, void *)));
	if (c == 'd' || c == 'i')
		return (print_nbr(va_arg(ap, int)));
	if (c == 'u')
		return (print_unsigned(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (print_hex(va_arg(ap, unsigned int), 0));
	if (c == 'X')
		return (print_hex(va_arg(ap, unsigned int), 1));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}
