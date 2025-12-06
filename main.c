#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
    int a;
    int b;

    // Hex test
    a = printf(" %x %x %x \n", 0, 15, 255);
    b = ft_printf(" %x %x %x \n", 0, 15, 255);
    printf("printf = %d, ft_printf = %d\n\n", a, b);

    // Pointer NULL test (matches TEST(9, print(" %p %p ", 0, 0));)
    a = printf(" %p %p \n", (void *)0, (void *)0);
    b = ft_printf(" %p %p \n", (void *)0, (void *)0);
    printf("printf = %d, ft_printf = %d\n", a, b);
    return (0);
}