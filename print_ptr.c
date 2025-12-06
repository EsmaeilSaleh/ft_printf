#include "ft_printf.h"

int print_ptr(void *p)
{
	unsigned long addr;
	int count;

	if (!p)
		return (write(1, "(nil)", 5));
	addr = (unsigned long)p;
	count = write(1, "0x", 2);
	count += print_hex(addr, 0);
	return (count);
}