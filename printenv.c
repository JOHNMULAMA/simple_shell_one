#include "shell.h"

/**
 * printenv - Prints the current environment.
 * @env: Pointer to an array of pointers to environment variables.
 *
 * Return: No return value.
 */
int printenv(char **env)
{
    char **my_env = env;

    while (*my_env)
    {
        write(STDOUT_FILENO, *my_env, _strlen(*my_env));
        write(STDOUT_FILENO, "\n", 1);
        my_env++;
    }
    return 0;
}
