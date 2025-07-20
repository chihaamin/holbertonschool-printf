#include "main.h"
/**
 * handle_int - Handles %d and %i specifiers (signed integers)
 * @args: va_list containing integer
 *
 * Logic:
 * 1. Extract integer from va_list
 * 2. Handle negative numbers (print '-' and convert to positive)
 * 3. Print absolute value using put_unsigned()
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_int(va_list *args)
{
	unsigned long num = (unsigned long long)va_arg(*args, int);
	int count = 0;

	/* Handle negative numbers */
	if (num < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);

		num = -num;
		count++;
	}

	int res = put_unsigned(num, 10, 0);

	return ((res == -1) ? -1 : count + res);
}

/**
 * handle_uint - Handles %u specifier (unsigned integers)
 * @args: va_list containing unsigned integer
 *
 * Logic:
 * 1. Pass to put_unsigned() with base 10
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_uint(va_list *args)
{
	unsigned long num = va_arg(*args, unsigned int);

	return (put_unsigned(num, 10, 0));
}

/**
 * handle_octal - Handles %o specifier (octal numbers)
 * @args: va_list containing unsigned integer
 *
 * Logic:
 * 1. Pass to put_unsigned() with base 8
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_octal(va_list *args)
{
	unsigned long num = va_arg(*args, unsigned int);

	return (put_unsigned(num, 8, 0));
}

/**
 * handle_ptr - Handles %p specifier (pointer addresses)
 * @args: va_list containing pointer
 *
 * Logic:
 * 1. Cast pointer to unsigned long
 * 2. Print "0x" prefix
 * 3. Print address in lowercase hexadecimal
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_ptr(va_list *args)
{
	void *ptr = va_arg(*args, void *);
	unsigned long addr = (unsigned long)ptr;
	int count = 0;
	unsigned long res;

	/* Print "0x" prefix */
	res = write(1, "0x", 2);
	if (res == -1)
		return (-1);
	count += res;

	/* Print hexadecimal address */
	res = put_unsigned(addr, 16, 0);
	if (res == -1)
		return (-1);

	return (count + res);
}
