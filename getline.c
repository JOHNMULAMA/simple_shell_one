#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    if (new_size == old_size)
        return ptr;

    if (ptr == NULL)
        return malloc(new_size);

    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return NULL;
    }

    void *mem = malloc(new_size);
    if (mem == NULL)
    {
        free(ptr);
        return NULL;
    }

    if (new_size < old_size)
        old_size = new_size;

    char *filler = mem;
    char *ptr_copy = ptr;
    for (unsigned int index = 0; index < old_size; index++)
        filler[index] = *ptr_copy++;

    free(ptr);
    return mem;
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
    if (*lineptr == NULL || b > *n)
    {
        if (b > 120)
            *n = b;
        else
            *n = 120;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}

/**
 * _getline - Reads input from a stream.
 * @lineptr: A buffer to store the input.
 * @n: The size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    static ssize_t input = 0;
    ssize_t ret;
    char c = 'x', *buffer;
    int r;

    if (input == 0)
        fflush(stream);
    else
        return -1;

    input = 0;

    buffer = malloc(sizeof(char) * 120);
    if (!buffer)
        return -1;

    while (c != '\n')
    {
        r = read(STDIN_FILENO, &c, 1);
        if (r == -1 || (r == 0 && input == 0))
        {
            free(buffer);
            return -1;
        }
        if (r == 0 && input != 0)
        {
            input++;
            break;
        }

        if (input >= 120)
            buffer = _realloc(buffer, input, input + 1);

        buffer[input] = c;
        input++;
    }
    buffer[input] = '\0';

    assign_lineptr(lineptr, n, buffer, input);

    ret = input;
    if (r != 0)
        input = 0;
    return ret;
}