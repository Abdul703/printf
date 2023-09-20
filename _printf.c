#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * check_buffer_and_flush - Check if the buffer is full and flush it if needed.
 *
 * @buffer: Buffer array
 * @buffer_index: Current buffer index
 */
void check_buffer_and_flush(char *buffer, int *buffer_index)
{
	if (*buffer_index == BUFFER_SIZE - 1)
	{
		write(1, buffer, *buffer_index);
		*buffer_index = 0;
	}
}

/**
 * _printf - Custom printf function that handles %, c, and s format specifiers.
 *
 * @format: String format
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list args;
	char buffer[BUFFER_SIZE], *str;
	int buffer_index = 0, character_count = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;

			switch (*format)
			{
				case '%':
					buffer[buffer_index++] = '%';
					check_buffer_and_flush(buffer, &buffer_index);
					character_count++;
					break;

				case 'c':
					buffer[buffer_index++] = va_arg(args, int);
					check_buffer_and_flush(buffer, &buffer_index);
					character_count++;
					break;

				case 's':
					str = va_arg(args, char *);
					while (*str)
					{
						buffer[buffer_index++] = *str++;
						check_buffer_and_flush(buffer, &buffer_index);
						character_count++;
					}
					break;

				default:
					buffer[buffer_index++] = '%';
					check_buffer_and_flush(buffer, &buffer_index);
					character_count++;
					break;
			}
		}
		else
		{
			buffer[buffer_index++] = *format;
			check_buffer_and_flush(buffer, &buffer_index);
			character_count++;
		}

		format++;
	}

	write(1, buffer, buffer_index);
	va_end(args);

	return (character_count);
}
