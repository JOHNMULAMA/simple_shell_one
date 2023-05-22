#include "shellheader.h"

/**

printenv - Prints the current environment.

@env: Pointer to an array of pointers to environment variables.

Return: No return value.
*/
int printenv(char **env)
{
char **my_env = env;
int len = 0;

while (my_env)
{
while ((*my_env + len))
len++;
write(STDOUT_FILENO, *my_env, len);
write(STDOUT_FILENO, "\n", 1);
len = 0;
my_env++;
}
return (0);
}