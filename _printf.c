#include "main.h"

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

	/* Search for matching specifier */
	for (int i = 0; i < count; i++)
	{
		if (handlers[i].symbol == specifier)
			return (handlers[i].handler(args));
	}

	/* Handle unknown specifier */
	return (handle_unknown(specifier));
}

/**
 * handle_format - Processes format specifiers in string
 * @args: va_list of arguments
 * @format: Pointer to current position in format string
 *
 * Logic:
 * 1. Skip '%' character
 * 2. Handle end-of-string case
 * 3. Dispatch to specifier handler
 *
 * Return: Number of characters printed or -1 on error
 */
int handle_format(va_list *args, const char **format)
{
	(*format)++;		  /* Skip '%' */
	if (**format == '\0') /* Handle trailing % */
		return (0);
	return (handle_specifier(args, **format));
}

/**
 * _printf - Custom printf implementation
 * @format: Format string with specifiers
 *
 * Core Logic:
 * 1. Initialize variable argument list
 * 2. Iterate through format string:
 *    - Literal characters: Print directly
 *    - '%' character: Process format specifier
 * 3. Maintain character count
 * 4. Cleanup va_list
 *
 * Special Considerations:
 * - Immediate return on write errors
 * - Handles nested format string advancement
 *
 * Return: Total characters printed or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	int res;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%') /* Format specifier */
		{
			res = handle_format(&args, &format);
			if (res == -1)
			{
				count = -1;
				break;
			}
			count += res;
		}
		else /* Literal character */
		{
			res = write(1, format, 1);
			if (res == -1)
			{
				count = -1;
				break;
			}
			count++;
		}
		format++; /* Advance to next character */
	}

	va_end(args);
	return (count);
}
