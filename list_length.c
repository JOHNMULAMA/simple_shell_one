#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings from a linked list
 * @head: pointer to the head of the linked list
 *
 * Return: array of strings, or NULL on failure
 */
char **list_to_strings(list_t *head)
{
	if (head == NULL)
	{
		return (NULL);
	}
	int list_size = 0,list_t *node = head;

	while (node)
	{
		list_size++;
		node = node->next;
	}

	if (list_size == 0)
	{
		return (NULL);
	}
	char **strs = malloc(sizeof(char *) * (list_size + 1));

	if (strs == NULL)
	{
		return (NULL);
	}
	int i = 0, node = head;

	while (node)
	{
		int str_length = _strlen(node->str);

		strs[i] = malloc(sizeof(char) * (str_length + 1));
		if (strs[i] == NULL)
		{
			for (int j = 0; j < i; j++)
				free(strs[j]), free(strs);
			return (NULL);
		}
		_strcpy(strs[i], node->str);
		i++;
		node = node->next;
	}
	strs[i] = NULL;
	return (strs);
}
