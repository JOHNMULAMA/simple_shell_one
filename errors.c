#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	return (write(2, &c, 1));
}

/**
 * _putfd - writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
 * _putsfd - prints an input string to the specified file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (*str)
	{
		i += _putfd(*str++, fd);
	}

	return (i);
}
