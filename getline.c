#include "shell.h"

/**
 *_getline - reads a line of characters from a stream
 *@n: buffer size
 *@fd: where to read the line
 *Return: Address of created buffer or NULL
 */
char *_getline(int n, int fd)
{
	int i = 0, bytes;
	char *buffer = NULL, ch;

	if (n == 0)
	{
		buffer = malloc(5);
		if (buffer == NULL)
		{
			free(buffer);
			return (NULL);
		}
		n = 5;
	}
	while (1)
	{
		bytes = read(fd, &ch, 1);
		if (bytes == -1)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		if (ch == EOF)
		{
			if (i == 0)
			{
				free(buffer);
				return (NULL);
			}
			else
				return (handle_line(buffer, i));
		}
		/* resize the buffer if not enough*/
		if (i >= (n - 1))
			buffer = resize(&n, buffer);
		buffer[i++] = ch; /* add character to buffer */
		if (ch == '\n') /* check if the character is a new line char */
			return (handle_line(buffer, i));
	}
}

/**
 * handle_line - handle end of line from getline
 * @buffer: the buffer to work on
 * @n: the last elemnt in buffer
 * Return: return the buffer
 */
char *handle_line(char *buffer, int n)
{
	buffer[n] = '\0';
	space_handle(buffer);
	hashtag_handle(buffer);
	return (buffer);
}
/**
 *resize - resize the buffer
 *@n: size of buffer
 *@buf: previous buffer
 *Return: new buffer created
 */
char *resize(int *n, char *buf)
{
	char *new;
	int new_size = (*n * 2), m = *n;

	new = _realloc(buf, new_size, m);
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	*n = new_size;

	return (new);
}

/**
 * hashtag_handle - remove everything after #
 * @buff: input;
 * Return:void
 */
void hashtag_handle(char *buff)
{
	int i;

		for (i = 0; buff[i] != '\0'; i++)
		{
			if (buff[i] == '#')
			{
			buff[i] = '\0';
			break;
			}
	}
}

/**
 *space_handle - strip spaces off the start and at the end of the string
 *@str: the string to strip
 *Return: void
 */
void space_handle(char *str)
{
	int start = 0, i;
	int end = _strlen(str) - 1;

	/* Find the first non-space character from the start */
	while (str[start] == ' ' || str[start] == '\t')
		start++;

	/* Find the first non-space character from the end */
	while (end >= start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
	{
		end--;
		str[end] = '\n';
	}

	/* Move the non-space characters to the beginning of the string */
	i = start;
	while (i <= end)
	{
		str[i - start] = str[i];
		i++;
	}
	str[end - start + 1] = '\0';
}
