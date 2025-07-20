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
static int put_unsigned(unsigned long n, int base, int uppercase)
{
	char buf[65];		  /* Buffer large enough for 64-bit numbers + null */
	char *ptr = buf + 64; /* Start at end of buffer */
	const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

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
	unsigned int len = (buf + 64) - ptr;

	return (write(1, ptr, len) == -1 ? -1 : len);
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
static int put_string(char *str)
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
