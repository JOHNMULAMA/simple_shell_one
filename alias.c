#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_ALIAS_COUNT 100
#define MAX_ALIAS_LENGTH 100

typedef struct {
	char name[MAX_ALIAS_LENGTH];
	char value[MAX_ALIAS_LENGTH];
} Alias;

static Alias alias_list[MAX_ALIAS_COUNT];
static int alias_count = 0;

/**
 * unset_alias - Unsets an alias.
 * @alias_name: The name of the alias to unset.
 *
 * Return: 0 on success, -1 on failure.
 */
int unset_alias(char *alias_name)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(alias_list[i].name, alias_name) == 0)
		{
			/* Shift the remaining aliases */
			for (; i < alias_count - 1; i++)
			{
				strcpy(alias_list[i].name, alias_list[i + 1].name);
				strcpy(alias_list[i].value, alias_list[i + 1].value);
			}
			alias_count--;
			return 0; /* Alias unset successfully */
		}
	}

	return -1; /* Alias not found */
}

/**
 * set_alias - Sets an alias to a string.
 * @alias_name: The name of the alias.
 * @alias_value: The value of the alias.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_alias(char *alias_name, char *alias_value)
{
	if (alias_count >= MAX_ALIAS_COUNT)
	{
		fprintf(stderr, "Maximum number of aliases reached.\n");
		return -1; /* Alias limit reached */
	}

	strcpy(alias_list[alias_count].name, alias_name);
	strcpy(alias_list[alias_count].value, alias_value);
	alias_count++;

	return 0; /* Alias set successfully */
}

/**
 * print_alias - Prints the value of an alias.
 * @alias_name: The name of the alias to print.
 *
 * Return: 0 on success, -1 on failure.
 */
int print_alias(char *alias_name)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(alias_list[i].name, alias_name) == 0)
		{
			printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
			return 0; /* Alias found and printed */
		}
	}

	return -1; /* Alias not found */
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @args: The arguments passed to the alias command.
 *
 * Return: 0 on success, -1 on failure.
 */
int _myalias(char **args)
{
	if (args[1] == NULL)
	{
		/* No arguments provided, print all aliases */
		int i;
		for (i = 0; i < alias_count; i++)
		{
			printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
		}
		return 0;
	}

	if (args[2] == NULL)
	{
		/* Only alias name provided, print the alias value */
		return print_alias(args[1]);
	}

	/* Both alias name and value provided, set the alias */
	return set_alias(args[1], args[2]);
}
