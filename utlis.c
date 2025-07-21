#include "main.h"

/**
 * put_unsigned - Converts and prints unsigned integers in any base
 * @n: Unsigned number to print
 * @base: Numerical base (2-16)
 * @uppercase: Hexadecimal uppercase flag (1 = uppercase, 0 = lowercase)
 *
 * Logic:
 * 1. Validate base (default to 10 if invalid)
 * 2. Create buffer on stack (65 bytes to handle 64-bit numbers)
 * 3. Fill buffer backwards with digits (reverse order)
 * 4. Handle zero as special case
 * 5. Write buffer content to stdout
 *
 * Return: Number of characters printed or -1 on error
 */
int put_unsigned(unsigned long n, unsigned int base, unsigned int uppercase)
{
    char buf[65];         /* Buffer large enough for 64-bit numbers + null */
    char *ptr = buf + 64; /* Start at end of buffer */
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int len;

    /* Base validation */
    if (base < 2 || base > 16)
        base = 10;

    *ptr = '\0'; /* Null-terminate string */

    /* Handle zero case */
    if (n == 0)
        *--ptr = '0';

    /* Convert number to string (backwards) */
    while (n)
    {
        *--ptr = digits[n % base]; /* Get digit and move pointer left */
        n /= base;
    }

    /* Calculate length and write */
    len = (buf + 64) - ptr;

    if (write(1, ptr, len) == -1)
        return (-1);
    return (len);
}

/**
 * put_string - Prints a string to stdout
 * @str: String to print (handles NULL)
 *
 * Logic:
 * 1. Replace NULL with "(null)"
 * 2. Calculate string length
 * 3. Write entire string in single system call
 *
 * Return: Number of characters printed or -1 on error
 */
int put_string(char *str)
{
    int len = 0;

    /* Handle NULL pointer */
    if (!str)
        str = "(null)";

    /* Calculate string length */
    while (str[len])
        len++;

    /* Write entire string at once */
    return (write(1, str, len) == -1 ? -1 : len);
}

/**
 * handle_unknown - Handles unknown specifiers
 * @c: Unknown specifier character
 *
 * Logic:
 * 1. Print '%' followed by the unknown character
 *
 * Return: 2 on success, -1 on error
 */
int handle_unknown(char c)
{
    int count = 0;
    int res;

    /* Print '%' */
    res = write(1, "%", 1);
    if (res == -1)
        return (-1);
    count += res;

    /* Print unknown character */
    res = write(1, &c, 1);
    if (res == -1)
        return (-1);

    return (count + res);
}

/**
 * handle_specifier - Dispatcher for format specifiers
 * @args: va_list of arguments
 * @specifier: Format specifier character
 *
 * Logic:
 * 1. Create dispatch table mapping specifiers to handlers
 * 2. Search table for matching specifier
 * 3. Call handler function or handle_unknown() if not found
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_specifier(va_list *args, char specifier)
{
    /* Dispatch table */
    const t_specifier handlers[] = {
        {'c', handle_char},
        {'s', handle_string},
        {'d', handle_int},
        {'i', handle_int},
        {'u', handle_uint},
        {'o', handle_octal},
        {'x', handle_hex_lower},
        {'X', handle_hex_upper},
        {'p', handle_ptr},
        {'%', handle_percent}};
    const int count = sizeof(handlers) / sizeof(handlers[0]);

    int i = 0;

    while (i < count)
    {
        if (handlers[i].symbol == specifier)
            return (handlers[i].handler(args));
        i++;
    }

    return (handle_unknown(specifier));
}

/**
 * handle_format - Processes format specifiers in string
 * @args: va_list of arguments
 * @format: Pointer to current position in format string
 *
 * Logic:
 * 1. Skip '%' character
 * 2. Delegate to helper function
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_format(va_list *args, const char **format)
{
    (*format)++;
    if (**format == '\0')
        return (0);

    return (handle_specifier(args, **format));
}
