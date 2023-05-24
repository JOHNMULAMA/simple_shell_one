#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * strtow - Splits a string into words. Repeat delimiters are ignored.
 * @str: The string to split.
 * @delim: The delimiter character.
 *
 * Return: An array of strings (words) or NULL on failure.
 */
char **strtow(char *str, char delim)
{
    if (str == NULL)
        return NULL;

    int i, j, k, word_count = 0;
    char **words = NULL;
    int len = strlen(str);

    for (i = 0; i < len; i++)
    {
        if (str[i] != delim)
        {
            word_count++;
            while (str[i] != delim && str[i] != '\0')
                i++;
        }
    }

    words = malloc((word_count + 1) * sizeof(char *));
    if (words == NULL)
        return NULL;

    words[word_count] = NULL;

    word_count = 0;
    for (i = 0; i < len;)
    {
        if (str[i] == delim)
        {
            i++;
            continue;
        }

        for (j = i; str[j] != delim && str[j] != '\0'; j++)
            ;

        words[word_count] = malloc((j - i + 1) * sizeof(char));
        if (words[word_count] == NULL)
        {
            for (k = 0; k < word_count; k++)
                free(words[k]);
            free(words);
            return NULL;
        }

        for (k = 0; i < j; i++, k++)
            words[word_count][k] = str[i];
        words[word_count][k] = '\0';
        word_count++;
    }

    return words;
}

/**
 * strtow2 - Splits a string into words.
 * @str: The string to split.
 *
 * Return: An array of strings (words) or NULL on failure.
 */
char **strtow2(char *str)
{
    if (str == NULL)
        return NULL;

    int i, j, k, word_count = 0;
    char **words = NULL;
    int len = strlen(str);

    for (i = 0; i < len;)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            i++;
            continue;
        }

        word_count++;
        while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
            i++;
    }

    words = malloc((word_count + 1) * sizeof(char *));
    if (words == NULL)
        return NULL;

    words[word_count] = NULL;

    word_count = 0;
    for (i = 0; i < len;)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            i++;
            continue;
        }

        for (j = i; str[j] != ' ' && str[j] != '\t' && str[j] != '\n' && str[j] != '\0'; j++)
            ;

        words[word_count] = malloc((j - i + 1) * sizeof(char));
        if (words[word_count] == NULL)
        {
            for (k = 0; k < word_count; k++)
                free(words[k]);
            free(words);
            return NULL;
        }

        for (k = 0; i < j; i++, k++)
            words[word_count][k] = str[i];
        words[word_count][k] = '\0';
        word_count++;
    }

    return words;
}

/**
 * is_chain - Tests if the current character in the buffer is a chain delimiter.
 * @c: The character to test.
 *
 * Return: 1 if the character is a chain delimiter, 0 otherwise.
 */
int is_chain(char c)
{
    return (c == ';' || c == '|' || c == '&');
}

/**
 * check_chain - Checks if we should continue chaining based on the last status.
 * @status: The status of the last executed command.
 *
 * Return: 1 if chaining should continue, 0 otherwise.
 */
int check_chain(int status)
{
    return (status == 0);
}

/**
 * replace_alias - Replaces aliases in the tokenized string.
 * @args: The tokenized string.
 *
 * Return: The updated tokenized string.
 */
char **replace_alias(char **args)
{
    // Sample implementation: no alias replacement
    return args;
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @args: The tokenized string.
 * @env: The environment variables.
 *
 * Return: The updated tokenized string.
 */
char **replace_vars(char **args, char **env)
{
    int i = 0;
    while (args[i] != NULL) {
        char *arg = args[i];
        if (arg[0] == '$') {
            char *var = &arg[1]; // Skip the leading '$'
            char *value = getenv(var);
            if (value != NULL) {
                free(args[i]);
                args[i] = strdup(value);
            }
        }
        i++;
    }
    return args;
}

/**
 * replace_string - Replaces a string with another string in the tokenized string.
 * @args: The tokenized string.
 * @old_str: The string to replace.
 * @new_str: The new string.
 *
 * Return: The updated tokenized string.
 */
char **replace_string(char **args, char *old_str, char *new_str)
{
    int i = 0;
    while (args[i] != NULL) {
        char *arg = args[i];
        char *pos = strstr(arg, old_str);
        if (pos != NULL) {
            size_t old_len = strlen(old_str);
            size_t new_len = strlen(new_str);
            size_t arg_len = strlen(arg);
            size_t diff_len = new_len - old_len;

            char *new_arg = malloc(arg_len + diff_len + 1);
            if (new_arg == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                return args;
            }

            // Copy the prefix before the old string
            strncpy(new_arg, arg, pos - arg);
            // Copy the new string
            strncpy(new_arg + (pos - arg), new_str, new_len);
            // Copy the suffix after the old string
            strcpy(new_arg + (pos - arg) + new_len, pos + old_len);

            free(args[i]);
            args[i] = new_arg;
        }
        i++;
    }
    return args;
}

int main(void)
{
    char line[] = "ls -l -a";
    char **args = strtow2(line);

    // Replace aliases
    args = replace_alias(args);

    // Replace variables
    char *env[] = { "PATH=/usr/bin", "HOME=/home/user", NULL };
    args = replace_vars(args, env);

    // Replace string
    char old_str[] = "-l";
    char new_str[] = "-la";
    args = replace_string(args, old_str, new_str);

    int i = 0;
    while (args[i] != NULL) {
        printf("%s\n", args[i]);
        i++;
    }

    // Free memory
    i = 0;
    while (args[i] != NULL) {
        free(args[i]);
        i++;
    }
    free(args);

    return 0;
}
