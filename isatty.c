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

int is_delim(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
	    c == ';' || c == '|' || c == '&' ||
	    c == '(' || c == ')' || c == '<' || c == '>')
		return (1);

	return (0);
}

/**
 * _isalpha - Checks if a character is an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);

	return (0);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to convert.
 *
 * Return: The converted integer.
 */
int _atoi(char *s)
{
	int sign = 1;
	int result = 0;
	int i = 0;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result = result * 10 + (s[i] - '0');
		}
		else
		{
			break;
		}
	}

	return (result * sign);
}