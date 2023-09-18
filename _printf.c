#include "main.h"
#include <stdarg.h>
#include <unistd.h>


/**
 * check_buffer_and_flush - check if buffer is full, then flush it
 *
 * @buffer: buffer array
 * @buffer_index: current buffer index
 *
 * Return: void
*/
void check_buffer_and_flush(char *buffer, int *buffer_index)
{
	if (BUFFER_SIZE - 1 == *buffer_index)
	{
		write(1, buffer, BUFFER_SIZE);
		*buffer_index = 0;
	}
}

/**
 * add_string_to_buffer - add string characters to buffer
 *
 * @buffer: buffer array
 * @buffer_index: current buffer index
 * @str: string to add
 *
 * Return: the count of characters in the string
*/
int add_string_to_buffer(char *buffer, int *buffer_index, char *str)
{
	int count = 0;

	while (*str != '\0')
	{
		buffer[(*buffer_index)++] = *str;
		check_buffer_and_flush(buffer, buffer_index);
		str++;
		count++;
	}
	return (count);
}

/**
 * _printf - custom printf function
 *
 * @format: string format
 *
 * Return: the number of character for the format string
*/
int _printf(const char *format, ...)
{
	va_list args;
	char buffer[BUFFER_SIZE], c, *str;
	int buffer_index = 0, character_count = 0;

	va_start(args, format);

	/* loop through each character of the format string provided */
	while (*format != '\0')
	{
		/* handle format specifier */
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
				c = va_arg(args, int);
				buffer[buffer_index++] = c;
				check_buffer_and_flush(buffer, &buffer_index);
				character_count++;
				break;

			case 's':
				str = va_arg(args, char *);
				character_count += add_string_to_buffer(buffer, &buffer_index, str);
				break;
			}
		}
		else /* handle ordinary characters */
		{
			buffer[buffer_index++] = *format;
			check_buffer_and_flush(buffer, &buffer_index);
			character_count++;
		}
		format++;
	}
	/* flush the remaining characters from buffer */
	write(1, buffer, buffer_index++);
	va_end(args);
	return (character_count);
}
