#include "main.h"
/**
 * handle_char - Handles %c specifier (single character)
 * @args: va_list containing character
 *
 * Logic:
 * 1. Extract char from va_list (promoted to int)
 * 2. Write single character
 *
 * Return: 1 on success, -1 on error
 */
int handle_char(va_list *args)
{

	char c = (char)va_arg(*args, int);

	return (write(1, &c, 1) == -1 ? -1 : 1);
}

/**
 * handle_string - Handles %s specifier (string)
 * @args: va_list containing string pointer
 *
 * Logic:
 * 1. Pass to put_string() for handling
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_string(va_list *args)
{
	char *str = va_arg(*args, char *);

	return (put_string(str));
}

/**
 * handle_hex - Base handler for hexadecimal conversions
 * @args: va_list containing unsigned integer
 * @uppercase: Letter case flag (0 = lowercase, 1 = uppercase)
 *
 * Logic:
 * 1. Pass to put_unsigned() with base 16 and case flag
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_hex(va_list *args, int uppercase)
{
	int num = va_arg(*args, unsigned int);

	return (put_unsigned((unsigned long long)num, 16, uppercase));
}

/**
 * handle_hex_lower - Handles %x specifier (lowercase hex)
 * @args: va_list containing unsigned integer
 *
 * Logic: Wrapper for handle_hex() with uppercase=0
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_hex_lower(va_list *args)
{
	return (handle_hex(args, 0));
}
/**
 * handle_hex_upper - Handles %X specifier (uppercase hex)
 * @args: va_list containing unsigned integer
 *
 * Logic: Wrapper for handle_hex() with uppercase=1
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_hex_upper(va_list *args)
{
	return (handle_hex(args, 1));
}
