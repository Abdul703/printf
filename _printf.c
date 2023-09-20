#include "main.h"
#include <stdarg.h>
#include <unistd.h>

int handle_char(char *buffer, int *buffer_index, int c);
int handle_string(char *buffer, int *buffer_index, char *str);
int handle_int(char *buffer, int *buffer_index, int num);

void check_buffer_and_flush(char *buffer, int *buffer_index)
{
	if (*buffer_index == BUFFER_SIZE - 1)
	{
		write(1, buffer, *buffer_index);
		*buffer_index = 0;
	}
}

int _printf(const char *format, ...)
{
	va_list args;
	char buffer[BUFFER_SIZE];
	int buffer_index = 0, character_count = 0;

	if (!format || !format[0])
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
					buffer[buffer_index++] = '%';
					check_buffer_and_flush(buffer, &buffer_index);
					character_count++;
					break;

				case 'c':
					character_count += handle_char(buffer, &buffer_index, va_arg(args, int));
					break;

				case 's':
					character_count += handle_string(buffer, &buffer_index, va_arg(args, char *));
					break;

				case 'd':
				case 'i':
					character_count += handle_int(buffer, &buffer_index, va_arg(args, int));
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

int handle_char(char *buffer, int *buffer_index, int c)
{
	buffer[(*buffer_index)++] = c;
	check_buffer_and_flush(buffer, buffer_index);
	return (1);
}

int handle_string(char *buffer, int *buffer_index, char *str)
{
	int count = 0;

	while (*str)
	{
		buffer[(*buffer_index)++] = *str++;
		check_buffer_and_flush(buffer, buffer_index);
		count++;
	}
	return (count);
}

int handle_int(char *buffer, int *buffer_index, int num)
{
	int sign = (num < 0) ? 1 : 0;
	int num_digits, temp, i;

	if (sign)
	{
		num = -num;
		buffer[(*buffer_index)++] = '-';
	}
	num_digits = 0;
	temp = num;
	do
	{
		temp /= 10;
		num_digits++;
	} while (temp != 0);
	char num_str[num_digits + 1];
	num_str[num_digits] = '\0';
	for (i = num_digits - 1; i >= 0; i--)
	{
		num_str[i] = (num % 10) + '0';
		num /= 10;
	}
	return (handle_string(buffer, buffer_index, num_str));
}
