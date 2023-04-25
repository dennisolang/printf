#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 *
 * _printf - Printf function
 *
 * @format: format.
 *
 * Return: Printed chars.
*/
int _printf(const char *format, ...)
{
	va_list list;
	int printed_chars = 0, buff_ind = 0;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	while (*format != '\0')
	{
		if (*format != '%')
		{
			buffer[buff_ind++] = *format++;
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			format++;
			printed_chars += handle_print(format, &list, buffer, &buff_ind);
			if (printed_chars == -1)
				return (-1);
		}
	}

	print_buffer(buffer, &buff_ind);
	va_end(list);

	return (printed_chars);
}

/**
 *
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
*/
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, buffer, *buff_ind);
		*buff_ind = 0;
	}
}
