#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * _cd - Changes the current working directory to the given directory.
 * @args: Parsed command line.
 * @env: Pointer to array of pointers to environment variables.
 *
 * Return: Always 0.
 */
int _cd(char **args, char **env)
{
	char *pwd, *cwd;
	int idx, status;

	pwd = _getenv("PWD", env);

	if (args[1] != NULL)
	{
		if (args[1][0] == '-')
		{
			cwd = _getenv("OLDPWD", env);
		}
		else if (args[1][0] == '$')
		{
			cwd = strtok(args[1], "$");
			cwd = strtok(NULL, " ");

			for (idx = 0; env[idx]; idx++)
			{
				if (_strncmp(env[idx], cwd, _strlen(cwd)) == 0)
				{
					cwd = _getenv(env[idx], env);
					break;
				}
			}
		}
		else
		{
			cwd = _strdup(args[1]);
		}
	}
	else
	{
		cwd = _getenv("HOME", env);
	}

	status = chdir(cwd);
	if (status == -1)
	{
		/* Handle error */
		perror("chdir");
	}
	else
	{
		_setenv("OLDPWD", pwd, env);
		_setenv("PWD", cwd, env);
	}

	free(cwd);
	free(pwd);
	return (status);
}
