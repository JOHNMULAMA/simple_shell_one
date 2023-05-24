#include "shell.h"

/**
 * history - Populates file with user input commands.
 * @input: Commands input by the user.
 * Return: 0 on success, -1 on error.
 */
int history(char *input)
{
	char *filename = ".simple_shell_history";
	ssize_t fd, w;
	int len = 0;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00600);
	if (fd < 0)
		return (-1);

	if (input)
	{
		while (input[len])
			len++;
		w = write(fd, input, len);
		if (w < 0)
			return (-1);
	}

	close(fd);
	return (0);
}

/**
 * disp_hist - Displays history of user input.
 * @c: Parsed command.
 * @s: Status of last execution.
 * Return: 0 on success, -1 on error.
 */
int disp_hist(__attribute__((unused)) char **c, __attribute__((unused)) int s)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int i = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return (-1);
	}

	while ((getline(&line, &len, fp)) != -1)
	{
		i++;
		er = tostring(i);
		PRINTER(er);
		free(er);
		PRINTER(" ");
		PRINTER(line);
	}

	if (line)
		free(line);

	fclose(fp);
	return (0);
}

/**
 * free_env - Frees environment variable array.
 * @env: Environment variables.
 * Return: void.
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		free(env[i]);
	}

	free(env);
}

/**
 * new_function - A new function to be added.
 * @arg1: Argument 1.
 * @arg2: Argument 2.
 * Return: Result of the function.
 */
int new_function(int arg1, int arg2)
{
	/* Function body */
	return arg1 + arg2;
}
