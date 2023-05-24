#include "shell.h"

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @var: pointer to name of environment variable
 * @value: pointer to value of environment variable
 * @env: pointer to array of pointers to the environment variables
 *
 * Return: 0 on success
 */
int _setenv(char *var, char *value, char **env)
{
    char *env_var;
    int xa = 0, var_len = 0, status = 0;

    var_len = _strlen(var);
    env_var = buildstr(var, "=", value);

    for (xa = 0; env[xa]; xa++)
    {
        if (_strncmp(env[xa], var, var_len) == 0)
        {
            free(env[xa]);
            env[xa] = strdup(env_var);
            status = 1;
            break;
        }
    }

    if (status != 1)
    {
        while (env[xa])
        {
            free(env[xa]);
            env[xa] = env[xa + 1];
            xa++;
        }
        env[xa] = _strdup(env_var);
        env[xa + 1] = NULL;
    }

    free(env_var);
    return 0;
}
