#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

int _putchar(char c);

/**
 * t_handler - Function pointer type for specifier handlers
 * @args: va_list of arguments
 * Return: Number of characters printed
 */
typedef int (*t_handler)(va_list *);

/**
 * struct s_specifier - Maps format specifiers to handler functions
 * @symbol: Format specifier character
 * @handler: Function pointer to handler
 */
typedef struct s_specifier
{
	char symbol;
	t_handler handler;
} t_specifier;

/* Main printf function */
int _printf(const char *format, ...);

/* Format processing functions */
int handle_format(va_list *args, const char **format);

int handle_specifier(va_list *args, char specifier);

/* Specifier handler functions */
int handle_char(va_list *args);
int handle_string(va_list *args);
int handle_int(va_list *args);
int handle_uint(va_list *args);
int handle_octal(va_list *args);
int handle_hex(va_list *args, int uppercase);

int handle_hex_lower(va_list *args);
int handle_hex_upper(va_list *args);
int handle_ptr(va_list *args);
int handle_percent(va_list *args);
int handle_unknown(char c);

/* Utility functions */
int put_string(char *str);
int put_unsigned(unsigned long n, unsigned int base, unsigned int uppercase);

#endif
