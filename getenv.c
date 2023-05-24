#include "shell.h"

/**
 * _getenv - get value of given environment variable
 * @var: pointer to Environment variable whose value is needed
 * @env: pointer to array of pointers to environment variables
 *
 * Return: pointer to retrieved value, or NULL on failure
 */
char *_getenv(char *var, char **env)
{
    int xa, var_len;
    char *env_var = NULL;

    var_len = _strlen(var);
    for (xa = 0; env[xa]; xa++)
    {
        if (_strncmp(env[xa], var, var_len) == 0)
        {
            env_var = env[xa];
            break;
        }
    }

    if (env_var != NULL)
    {
        env_var = _strtok(env_var, "=");
        env_var = _strtok(NULL, "=");
    }

    return env_var;
}
