#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *fmt, ...);
int		handle_format(char c, va_list ap);
int		print_char(char c);
int		print_str(char *s);
int		print_nbr(int n);
int		print_unsigned(unsigned int n);
int		print_hex(unsigned long n, int upper);
int		print_ptr(void *p);

#endif
