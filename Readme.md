*This project has been created as part of the 42 curriculum by sbouadai.*

# ft_printf

## Description

`ft_printf` is a recode of the C standard library function `printf`. The goal of the project is to build a static library, `libftprintf.a`, that exposes a function with the same prototype and behavior as the original for a defined set of conversions:

```c
int	ft_printf(const char *format, ...);
```

It returns the number of characters printed, like `printf`, and uses only `write` for output.

The project teaches how variadic functions work in C (`<stdarg.h>`), how to convert numbers to text in different bases without the standard library, how to parse a format string, and how to split a task into small functions that respect the 42 Norm.

### Mandatory part

| Specifier | Output |
|---|---|
| `%c` | a single character |
| `%s` | a string (`(null)` if the pointer is `NULL`) |
| `%p` | a pointer in hexadecimal, prefixed with `0x` (`(nil)` if `NULL`) |
| `%d` / `%i` | a signed decimal integer |
| `%u` | an unsigned decimal integer |
| `%x` / `%X` | an unsigned hexadecimal integer, lowercase / uppercase |
| `%%` | a literal percent sign |

### Bonus part

The bonus adds the flags, the field width and the precision, in the standard order:

```
%  [flags]  [width]  [.precision]  specifier
```

| Element | Meaning |
|---|---|
| `-` | left-justify inside the field width |
| `0` | pad with zeros instead of spaces (ignored with `-`, or with a precision on integers) |
| `.` | precision: minimum digits for integers, maximum characters for `%s` |
| width | minimum field width, never truncates |
| `#` | `0x` / `0X` prefix for `%x` / `%X` (only when the value is not 0) |
| `+` | always show the sign of a signed number |
| space | put a space before a positive signed number (ignored if `+` is present) |

## Instructions

### Compilation

The library is built with `cc` and the flags `-Wall -Wextra -Werror`.

```sh
make         # builds libftprintf.a (mandatory part)
make bonus   # builds libftprintf.a (bonus part)
make clean   # removes the object files
make fclean  # removes the object files and libftprintf.a
make re      # fclean followed by make
```

Both versions produce the same `libftprintf.a`. Building one replaces the other, and running the same target twice does not relink.

### Usage

Include the header and link your program against the library:

```c
#include "ft_printf.h"

int	main(void)
{
	int	len;

	len = ft_printf("Hello %s, you are %d years old\n", "world", 42);
	ft_printf("%d characters printed\n", len);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a -o demo
./demo
```

With the bonus library, include `ft_printf_bonus.h` instead:

```c
ft_printf("[%-8.3d] [%+05d] [%#010x] [%.3s]\n", 7, 42, 255, "abcdef");
```

Rebuild your test program every time the library changes, otherwise an old binary may be linked against old code.

### Project structure

```
.
├── Makefile
├── ft_printf.h
├── ft_printf.c
├── ft_print_char.c         %c, %s
├── ft_print_nbr.c          %d, %i, %u
├── ft_print_hex.c          %x, %X
├── ft_print_ptr.c          %p
│
├── ft_printf_bonus.h
├── ft_printf_bonus.c       main loop and dispatcher
├── format_check_bonus.c    parser for flags, width and precision
├── ft_print_char_bonus.c   %c
├── ft_print_str_bonus.c    %s
├── ft_print_nbr_bonus.c    %d, %i
├── ft_print_unbr_bonus.c   %u
├── ft_print_hex_bonus.c    %x, %X
├── ft_print_ptr_bonus.c    %p
└── ft_utils_bonus.c        helpers shared by the bonus files
```

## Algorithm and design

### Main loop

`ft_printf` walks through the format string one character at a time:

1. A normal character is written as is.
2. A `%` starts a conversion: the program reads the matching argument and calls the right print function.
3. Every print function returns the number of characters it wrote, and `ft_printf` adds them to a running total.
4. If the format ends right after a `%`, the function stops and returns `-1`.

### Reading the arguments

Arguments come from a `va_list`, initialized with `va_start`, read with `va_arg` and closed with `va_end`. The type given to `va_arg` must match the type the caller passed, because C stores no type information for variadic arguments:

| Specifier | Type read with `va_arg` |
|---|---|
| `%c` | `int` (a `char` is promoted to `int`) |
| `%s` | `char *` |
| `%d`, `%i` | `int` |
| `%u`, `%x`, `%X` | `unsigned int` |
| `%p` | `unsigned long` (a pointer is 8 bytes on a 64-bit system) |

The `va_list` is passed by pointer to the helper functions, so that every argument consumed in a helper also advances the list in the caller.

### Bonus: parsing the format

The parser reads the conversion in four ordered stages and stores the result in a structure:

```c
typedef struct s_flags
{
	int	minus;
	int	zero;
	int	dot;
	int	hash;
	int	plus;
	int	space;
	int	width;
	int	precision;
	int	letter;
}	t_flags;
```

1. **Flags:** loop while the character is one of `- 0 # + space`. Repeating a flag is allowed.
2. **Width:** read the digits.
3. **Precision:** if there is a `.`, set `dot` and read the digits (no digits means a precision of 0).
4. **Specifier:** the next character must be one of `cspdiuxX%`.

The stages never go back, so a flag after the width (`%5-d`) lands on the specifier check and fails. `dot` is kept separate from `precision`, because `%.0d` and `%d` behave differently for the value 0.

An invalid conversion is printed as plain text, from the `%` up to the character that stopped the parser, and no argument is consumed.

### Design choices

- **Recursion instead of a buffer** avoids `malloc` and fixed-size arrays, and keeps each function short.
- **One structure for the format** keeps functions under the Norm limit of four parameters.
- **A fixed print order** means no separate algorithm per flag combination: once the counts are computed, printing is the same for every case.
- **Small single-purpose functions**, split across files, to respect the Norm limits (25 lines, 5 functions per file).

## Testing

The output and the return value of `ft_printf` were compared with the real `printf`, using test programs that redirect both functions to temporary files and compare the two results. The tests cover every specifier, `0`, `INT_MIN`, `INT_MAX`, `UINT_MAX`, `NULL` strings and pointers, stack addresses, every flag combination for integers and hexadecimal, widths and precisions around the length of the value, and invalid or incomplete formats.

## Resources

- `man 3 printf`, `man 3 stdarg`
- [Variadic Functions in C](https://www.geeksforgeeks.org/c/variadic-functions-in-c/) — A simple toturial to understanding Variadic Functions
- [All you need to know about variadic functions](https://youtu.be/7Sph8JlRo0g?si=QJBoGW00Vtk_8gNg) — A youtube video about variadic functions

### Use of AI

An AI assistant was used as a tutor during this project: to explain how variadic functions and `va_list` work internally, to explain the behavior of the real `printf` for flags, width and precision, and to generate test programs that compare `ft_printf` with `printf`. The code of the library was written by me, and every explanation and suggestion was checked by compiling and testing it.