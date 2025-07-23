#include "main.h"

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
			if (*(format + 1) == '\0') /* Handle trailing '%' */
			{
				res = write(1, "%", 2);
				count++;
				return (count);
			}

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
