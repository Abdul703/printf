#include "main.h"
#include <unistd.h>

/**
 * handle_default - handle normal characters
 *
 * @c: character to add
 * @buffer_index: current index of buffer
 * @buffer: what hold the characters to print
 *
 * Return: 2
 */
int handle_default(char *buffer, int *buffer_index, int c)
{
	buffer[(*buffer_index)++] = '%';
	check_buffer_and_flush(buffer, buffer_index);
	buffer[(*buffer_index)++] = c;
	check_buffer_and_flush(buffer, buffer_index);
	return (2);
}

/**
 * handle_char - add character to buffer
 *
 * @c: character to add
 * @buffer_index: current index of buffer
 * @buffer: what hold the characters to print
 *
 * Return: 1
 */
int handle_char(char *buffer, int *buffer_index, int c)
{
	buffer[(*buffer_index)++] = c;
	check_buffer_and_flush(buffer, buffer_index);
	return (1);
}

/**
 * handle_cent - add percent to buffer
 *
 * @buffer_index: current index of buffer
 * @buffer: what hold the characters to print
 *
 * Return: 1
 */
int handle_cent(char *buffer, int *buffer_index)
{
	buffer[(*buffer_index)++] = '%';
	check_buffer_and_flush(buffer, buffer_index);
	return (1);
}

/**
 * handle_string - add string to buffer
 *
 * @str: string to add
 * @buffer_index: current index of buffer
 * @buffer: what hold the characters to print
 *
 * Return: length of the string
 */
int handle_string(char *buffer, int *buffer_index, char *str)
{
	int count = 0;

	if (!str)
		str = "(null)";
	while (*str != '\0')
	{
		buffer[(*buffer_index)++] = *str++;
		check_buffer_and_flush(buffer, buffer_index);
		count++;
	}
	return (count);
}

/**
 * handle_int - add integer to buffer
 *
 * @n: number to add
 * @buffer_index: current index of buffer
 * @buffer: what hold the characters to print
 *
 * Return: length of the integer
 */
int handle_int(char *buffer, int *buffer_index, int n)
{
	int divisor = 1, count = 0, digit;
	unsigned int num = n;

	/* handle 0 */
	if (n == 0)
	{
		buffer[(*buffer_index)++] = '0';
		check_buffer_and_flush(buffer, buffer_index);
		return (1);
	}

	/* handle negative numbers */
	if (n < 0)
	{
		buffer[(*buffer_index)++] = '-';
		num *= -1;
		count++;
		check_buffer_and_flush(buffer, buffer_index);
	}

	/* get highest divisor */
	while (num / divisor >= 10)
		divisor *= 10;

	/* printing the numbers */
	while (divisor > 0)
	{
		digit = (num / divisor) % 10;
		buffer[(*buffer_index)++] = (digit + '0');
		divisor /= 10;
		count++;
		check_buffer_and_flush(buffer, buffer_index);
	}
	return (count);
}
