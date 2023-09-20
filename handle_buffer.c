#include "main.h"
#include <unistd.h>

/**
 * check_buffer_and_flush -check if buffer is full, print it and reset it
 *
 * @buffer: array of characters
 * @buffer_index: length of the buffer
 *
 * Return: void
*/
void check_buffer_and_flush(char *buffer, int *buffer_index)
{
	if (*buffer_index == BUFFER_SIZE - 1)
	{
		write(1, buffer, *buffer_index);
		*buffer_index = 0;
	}
}
