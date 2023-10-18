#include "shell.h"

/**
 * free_all - Free Array Of Char Pointer And Char Pointer
 * @cmd:Array Pointer
 * @line:Char Pointer
 * Return: Void
 */
void free_all(char **cmd, char *line)
{
	free(cmd);
	free(line);
	cmd = NULL;
	line = NULL;
}

/**
 *_realloc - re-allocate dynamic memory with new size
 *@previous: previously allocated memory
 *@n: the new size to use in allocation
 *@m: the old size of the allocated memory
 *Return: pointer to newly allocated memory or NULL
 */
void *_realloc(void *previous, int n, int m)
{
	void *new;

	if (n == 0)
	{
		free(previous);
		return (NULL);
	}
	if (previous == NULL)
	{
		new = malloc(n);
		return (new);
	}
	new = malloc(n);
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	/* copy data from previous to new allocated memory */
	if (n < m)
		m = n;
	_memcpy(new, previous, m);
	return (new);
}

/**
 *_memcpy - copy data from one memory block to another
 *@new: new memory to copy to
 *@old: old memory to compy from
 *@n: amount of data to copy
 *Return: nothing
 */
void _memcpy(void *new, void *old, int n)
{
	int i;
	char *dest = (char *)new, *src = (char *)old;


	for (i = 0; i < n; i++)
		*(dest + i) = *(src + i);
	free(src);
}

/**
 * fill_an_array - Fill An Array By Constant Byte
 * @a:Void Pointer
 * @el: Int
 * @len:Length Int
 *Return: Void Pointer
 */
void *fill_an_array(void *a, int el, unsigned int len)
{
	char *p = a;
	unsigned int i = 0;

	while (i < len)
	{
		*p = el;
		p++;
		i++;
	}
	return (a);
}
/**
 * _calloc -  Allocates Memory For An Array, Using Malloc.
 * @size: Size
 * Return: Void Pointer
 */
void *_calloc(unsigned int size)
{
	char *a;
	unsigned int i;

	if (size == 0)
	return (NULL);
	a = malloc(size);
	if (a == NULL)
	return (NULL);
	for (i = 0; i < size; i++)
	{
		a[i] = '\0';
	}
	return (a);
}
