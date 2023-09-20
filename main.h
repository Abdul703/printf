#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024

int _printf(const char *format, ...);
void check_buffer_and_flush(char *buffer, int *buffer_index);

int handle_char(char *buffer, int *buffer_index, int c);
int handle_default(char *buffer, int *buffer_index, int c);
int handle_cent(char *buffer, int *buffer_index);
int handle_string(char *buffer, int *buffer_index, char *str);
int handle_int(char *buffer, int *buffer_index, int n);

#endif
