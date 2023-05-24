#include "shell.h"
#include <unistd.h>

/**
 * interactive - Checks if the shell is running in interactive mode.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int interactive(void)
{
	return (isatty(STDIN_FILENO));
}
