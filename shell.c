#include "shell.h"

/**
 * main - A basic shell that executes commands with their full path, without any arguments.
 *
 * @argc: The number of arguments passed to the function.
 * @argv: An array of strings representing the arguments.
 *
 * Return: Always 0.
 */
int main(int argc attribute((unused)), char **argv)
{
    ssize_t k = 0;
    char **args, *my_env[60], *command = NULL;

    signal(SIGINT, handle_sigint);

    for (k = 0; environ[k]; k++)
        my_env[k] = _strdup(environ[k]);
    my_env[k] = NULL;

    while (1)
    {
        k = isatty(STDIN_FILENO);
        if (k == 1)
            write(STDOUT_FILENO, "$ ", 2);

        command = _getline(argv);
        if (command != NULL)
        {
            args = parsecommand(command);
            if (args == NULL)
            {
                perror(argv[0]);
            }
            else if (_strcmp(args[0], "exit") == 0)
            {
                shell_exit(args, my_env, command);
                break;
            }
            else
            {
                exec_func(args, my_env, argv);
                free_2d(args);
                free(args);
            }
        }
        else
        {
            perror(argv[0]);
        }

        free(command);
    }

    free_2d(my_env);
    return 0;
}
