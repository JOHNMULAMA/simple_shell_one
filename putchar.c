#include "shell.h"

/**
 * _putchar - Prints a character to STDOUT.
 * @c: The character to be printed.
 *
 * Return: 1 on success, -1 on error and errno set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
