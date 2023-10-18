#include "shell.h"
/**
 *_strtok - tokenizes a string based on a set of delimiter characters
 *@str: the string to tokenize
 *@delim: A string containing a set of delimiter characters
 *@save_point: where the next token is saved
 *Return: address of the generated token
 */
char *_strtok(char *str, char *delim, char **save_point)
{
	char *ch;
	size_t i = 0;

	if (str == NULL)
		str = *save_point;
	if (str == NULL)
		return (NULL); /* return NULL if we have reached the end */

	/* get the delimitor character position*/
	ch = get_delim(str, delim);
	while (*(str + i) != '\0')
	{
		if (str + i == ch)
		{
			if (*(str + i + 1) != '\0')
				(*save_point) = (str + i) + 1;
			else
				(*save_point) = NULL;
			*(str + i) = '\0';
			return (str);
		}
		i++;
	}
	return (NULL);
}

/**
 *get_delim - get the address where the delimitor is found
 *@str: the string to check
 *@delim: delimitor string
 *Return: Address where delimitor is found or NULL
 */
char *get_delim(char *str, char *delim)
{
	if (str != NULL && delim != NULL)
	{
		size_t i = 0, j;

		while (*(str + i) != '\0')
		{
			j = 0;
			while (*(delim + j) != '\0')
			{
				if (*(str + i) == *(delim + j))
					return (str + i);
				j++;
			}
			i++;
		}
	}
	return (NULL);
}

/**
 *_strtok2 - tokenizes a string based on a set of delimiter characters
 *@str: the string to tokenize
 *@save_point: where the next token is saved
 *Return: address of the generated token
 */
char *_strtok2(char *str, char **save_point)
{
	char *ch;
	size_t i = 0;

	if (str == NULL)
		str = *save_point;
	if (str == NULL)
		return (NULL); /* return NULL if we have reached the end */

	/* get the delimitor character position*/
	ch = get_delim2(str);
	while (*(str + i) != '\0')
	{
		if (str + i == ch)
		{
			if (*(str + i + 1) != '\0')
			{
				if (*ch == ';')
					(*save_point) = (str + i) + 2;
				else
					(*save_point) = (str + i) + 3;
			}
			else
				(*save_point) = NULL;
			if (*(str + i - 1) == ' ')
				*(str + i - 1) = '\0';
			else
				*(str + i) = '\0';
			return (str);
		}
		i++;
	}
	return (NULL);
}

/**
 *get_delim2 - get the address where the delimitor is found
 *@str: the string to check
 *Return: Address where delimitor is found or NULL
 */
char *get_delim2(char *str)
{
	if (str != NULL)
	{
		size_t i = 0;

		while (*(str + i) != '\0')
		{
			if (*(str + i) == '&' && *(str + i + 1) == '&')
				return (str + i);
			if (*(str + i) == ';')
				return (str + i);
			if (*(str + i) == '|' && *(str + i + 1) == '|')
				return (str + i);
			if (*(str + i) == '\n')
				return (str + i);
			i++;
		}
	}
	return (NULL);
}
