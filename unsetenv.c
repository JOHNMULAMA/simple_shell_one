#include "shell.h"

/**
 * _unsetenv - Removes an environment variable.
 * @var: Name of the variable to be removed.
 * @env: Pointer to an array of pointers to environment variables.
 *
 * Return: 0 on success.
 */
int _unsetenv(char *var, char **env)
{
    char **temp;
    int var_len;

    var_len = _strlen(var);
    while (*env)
    {
        if (_strncmp(*env, var, var_len) == 0 && (*env)[var_len] == '=')
        {
            temp = env;
            free(*temp);
            do {
                env[0] = env[1];
                temp++;
            } while (*temp);
        }
        else
        {
            env++;
        }
    }
    return 0;
}