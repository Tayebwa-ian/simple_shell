#include "shell.h"

/**
 * *_getpath - get path to executable by using PATH
 *@cmd: the input command that has the executable file name
 *Return: Address of buffer on success of NULL on failure
 */
char *_getpath(char *cmd)
{
	char *path, *token, *delim, *temp, *buffer;

	delim = ":\n";
	if (cmd != NULL)
	{
		/* get the path and deal with it*/
		path = _getenv("PATH");
		token = _strtok(path, delim, &temp);
		while (token != NULL)
		{
			buffer = build(token, cmd, "/");
			/*check if file exists in created path */
			if (access(buffer, F_OK) == 0)
				return (buffer);
			token = _strtok(NULL, delim, &temp);
			free(buffer);
		}
	}
	temp = NULL;
	return (NULL);
}

/**
 * build - Build Command
 * @token: directory containing command
 * @cmd: command given from input
 * @ch: the character to put between strings
 * Return: Parsed Full Path Of Command Or NULL Case Failed
 */
char *build(char *token, char *cmd, char *ch)
{
	char *path;
	size_t len;

	len = _strlen(cmd) + _strlen(token) + 2;
	path = malloc(sizeof(char) * len);
	if (path == NULL)
		return (NULL);

	memset(path, 0, len);

	path = _strcat(path, token);
	path = _strcat(path, ch);
	path = _strcat(path, cmd);

	return (path);
}

/**
 *_getenv - getting an enviroment variable
 *@name: name of the variable to get
 *Return: the value stored in a variable or NULL when it fals
 */
char *_getenv(char *name)
{
	char *equal_sign, *var_name;
	int i = 0;
	size_t var_len;

	while (environ[i] != NULL)
	{
		var_name = environ[i];
		/* get the position of equal sign to separate var from value*/
		equal_sign = _strchr(var_name, '=');

		if (equal_sign == NULL)
			continue;

		var_len = equal_sign - var_name;
		/* compare the given name with name variable*/
		if (_strncmp(name, var_name, var_len) == 0)
			return (equal_sign + 1);

		i++;
	}
	return (NULL);
}
