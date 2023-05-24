#include "shell.h"

/**
 * shell_exit - Exits the shell with the given status.
 *
 * @args: Arguments passed on the command line.
 * @env: Double pointer to environment variables.
 * @command: Pointer to the string read from stdin.
 *
 * Return: No return value.
 */
void shell_exit(char **args, char **env, char *command)
{
    int status = 0;

    if (args[1] != NULL)
    {
        status = toint(args[1]);
    }

    free(command);
    free_2d(env);
    free_2d(args);
    free(args);
    exit(status);
}
