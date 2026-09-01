_This project has been created as part of the 42 curriculum by esaleh._

# ft_printf

## Description

`ft_printf` is a reimplementation of the C standard library `printf`,
built as a static library (`libftprintf.a`). The goal is to reproduce the
formatted-output behaviour of `printf` for the conversions required by the
42 subject, using only `write` and a variadic argument list.

The library exposes a single public function:

```c
int ft_printf(const char *fmt, ...);
```

It walks the format string, prints literal characters directly, and for
each `%` conversion pulls the matching argument from the `va_list` and
formats it. The return value is the total number of characters written,
matching `printf`.

### Supported conversions

| Specifier   | Prints                                                |
| ----------- | ----------------------------------------------------- |
| `%c`        | a single character                                    |
| `%s`        | a string (`(null)` if the pointer is `NULL`)          |
| `%p`        | a pointer as `0x` + lowercase hex (`(nil)` if `NULL`) |
| `%d` / `%i` | a signed decimal `int`                                |
| `%u`        | an unsigned decimal `int`                             |
| `%x` / `%X` | an unsigned `int` in lower / upper hex                |
| `%%`        | a literal `%`                                         |

Flags, field width, and precision are out of scope (mandatory part only).
An unknown specifier prints nothing; a lone trailing `%` ends the scan and
returns the running count.

## Instructions

### Build

```sh
make          # builds libftprintf.a
make clean    # removes object files
make fclean   # removes object files and the library
make re       # fclean + build
```

Compiled with `cc -Wall -Wextra -Werror`.

### Use

Include the header and link the archive:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s, %d in hex is %#x... actually just %x\n",
              "world", 255, 255, 255);
    return (0);
}
```

```sh
cc main.c -L. -lftprintf -I. -o program
./program
```

A `main.c` is included that diffs `ft_printf` against the system `printf`
for a few cases; build it manually with the command above.

## Algorithm and data structure

The subject requires justifying the chosen algorithm and data structure.
There is no container type here — the design is a small dispatch loop plus
per-type digit conversion.

### Dispatch

`ft_printf` scans `fmt` character by character. Literals go straight to
`write`. On `%`, the next character is passed to `handle_format`, which is
a flat `if` chain mapping specifier to a `print_*` helper and the matching
`va_arg` type. A flat chain was chosen over a lookup table because the set
of specifiers is small and fixed; a table of function pointers would need
uniform signatures and extra indirection for no readable gain.

Each `print_*` helper returns its own character count, which the caller
accumulates. This keeps the length bookkeeping local to the code that
actually emits the bytes.

### Number-to-string conversion

Signed (`print_nbr`), unsigned (`print_unsigned`) and hex (`print_hex`)
all use the same approach:

1. Compute the digit count with a small `*_len` helper (repeated division
   by the base).
2. Use a fixed `char buffer[32]` on the stack as scratch space — 32 bytes
   covers any 64-bit value in base 10 or 16 with room for a sign, so no
   dynamic allocation is needed and the size can never be exceeded.
3. Fill the buffer back to front: take `value % base` for the least
   significant digit, write it at the highest free index, divide by
   `base`, move left.
4. Emit the buffer with a single `write` of the known length.

Writing back-to-front avoids reversing the string afterwards. A
stack buffer is used rather than character-by-character recursion or
`malloc` because the maximum size is known at compile time, giving
constant space and one syscall per conversion.

`print_nbr` widens `int` to `long` before taking the absolute value so
that `INT_MIN` does not overflow when negated. `print_ptr` casts the
pointer to `unsigned long` and reuses `print_hex` for the address body.

## Resources

- `man 3 printf` — reference behaviour and return value.
- `man 3 stdarg` — `va_start`, `va_arg`, `va_end`, `va_list`.
- [cppreference: variadic functions](https://en.cppreference.com/w/c/variadic)
- [cppreference: fprintf family](https://en.cppreference.com/w/c/io/fprintf)

### Use of AI

To draft the conversion table, build/usage instructions, and the write-up of the
dispatch loop and the back-to-front buffer conversion. All library code
(`ft_printf.c`, `handle_format.c`, and the `print_*` helpers) was written
by hand; AI was not used to generate or modify it.
