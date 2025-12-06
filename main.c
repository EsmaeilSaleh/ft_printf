#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
    int a;
    int b;

    a = printf(" %x %x %x \n", 0, 15, 255);
    b = ft_printf(" %x %x %x \n", 0, 15, 255);
    printf("printf = %d, ft_printf = %d\n", a, b);
    return (0);
}