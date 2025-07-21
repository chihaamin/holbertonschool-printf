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
	int n = va_arg(*args, int);
	int count = 0;
	unsigned long abs_n;
	int res;

	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		count++;
		if (n == INT_MIN)
			abs_n = (unsigned long)INT_MAX + 1;
		else
			abs_n = (unsigned long)(-n);
	}
	else
	{
		abs_n = (unsigned long)n;
	}

	res = put_unsigned(abs_n, 10, 0);
	if (res == -1)
		return (-1);
	return (count + res);
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
	unsigned int n = va_arg(*args, unsigned int);

	return (put_unsigned((unsigned long)n, 10, 0));
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
	unsigned long n = va_arg(*args, unsigned int);
	int res;

	res = put_unsigned(n, 8, 0);

	return (res);
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
	int res;
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

/**
 * handle_percent - Handles %% specifier (percent sign)
 * @args: Unused va_list
 *
 * Logic: Prints literal '%' character
 *
 * Return: 1 on success, -1 on error
 */
int handle_percent(va_list *args)
{
	(void)args; /* Unused parameter */
	return (write(1, "%", 1) == -1 ? -1 : 1);
}
