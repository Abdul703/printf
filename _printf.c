#include "main.h"
#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - a custom printf
 *
 * @format: string format
 *
 * Return: length of string format
*/
int _printf(const char *format, ...)
{
	va_list args;
	char buffer[BUFFER_SIZE], *str;
	int buffer_index = 0, character_count = 0;

	if (!format || !format[0] || (format[0] == '%' && !format[1]))
		return (-1);

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case '%':
				character_count += handle_cent(buffer, &buffer_index);
				break;

			case 'c':
				character_count += handle_char(buffer, &buffer_index, va_arg(args, int));
				break;

			case 's':
				str = va_arg(args, char *);
				character_count += handle_string(buffer, &buffer_index, str);
				break;

			case 'd':
			case 'i':
				character_count += handle_int(buffer, &buffer_index, va_arg(args, int));
				break;

			default:
				character_count += handle_default(buffer, &buffer_index, *format);
				break;
			}
		}
		else
		{
			character_count += handle_char(buffer, &buffer_index, *format);
		}
		format++;
	}

	write(1, buffer, buffer_index);
	va_end(args);

	return (character_count);
}
