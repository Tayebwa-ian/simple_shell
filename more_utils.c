#include "shell.h"

/**
 * get_tokens - generate tokens of the input
 * @input:User Input To tokenize
 * Return: Array Of tokens
 */
char **get_tokens(char *input)
{
	char **tokens, *token, *temp;
	int i, buffsize = BUFSIZE;

	temp = NULL;

	if (input == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * buffsize);
	if (!tokens)
	{
		perror("hsh");
		return (NULL);
	}

	token = _strtok(input, "\n ", &temp);
	for (i = 0; token; i++)
	{
		tokens[i] = token;
		token = _strtok(NULL, "\n ", &temp);
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 *_putenv - Managinig environment variables
 *@var: the vraible to work with
 *Return: 0 on success and -1 on failure
 */
int _putenv(char *var)
{
	char *equals, *new_var, **env;
	size_t name_len, value_len, tmp;

	env = environ;
	if (var == NULL || var[0] == '\0')
		return (-1);

	equals = _strchr(var, '=');

	if (equals == NULL)
		return (-1);

	/* Calculate the length of the variable name and value */
	name_len = equals - var;
	value_len = _strlen(equals) + 1;

	while (*env != NULL)
	{
		/* Check if the variable name matches */
		if (_strncmp(var, *env, name_len) == 0 &&
		    (*env)[name_len] == '=')
		{
			/* Update the existing environment variable*/
			_strcpy(*env, var);
			return (0);
		}
		env++;
	}

	/* If the variable doesn't exist, allocate memory for it */
	new_var = (char *)malloc(name_len + value_len + 2);
	if (new_var == NULL)
		return (-1);

	strcpy(new_var, var);
	tmp = environ_size();
	environ[tmp] = new_var;
	environ[tmp + 1] = NULL;

	return (0);
}

/**
 * environ_size - Calculate the size of env
 * Return: size of the env
 */
int environ_size(void)
{
	int size = 0;

	while (environ[size] != NULL)
		size++;
	return (size);
}

/**
 * chain_cmds - execute chain commands
 * @input: the input from the stdin or a file
 * @counter:Shell Excution Time Case of Command Not Found
 * @argv:Program Name
 * @ch: character used in chaining
 * Return: Void
 */
void chain_cmds(char *input, int counter, char **argv, char *ch)
{
	char *token, **cmd, *save, *temp;
	int st;

	token = _strtok2(input, &save);
	while (token != NULL)
	{
		temp = put_char(token, '\n');
		cmd = get_tokens(temp);
		st = run_cmd(cmd, input, counter, argv);
		if (*ch == '|' && st == 0)
		{
			free(cmd);
			free(temp);
			break;
		}
		free(cmd);
		free(temp);
		token = _strtok2(NULL, &save);
	}
}
/**
 * put_char - Insert a character at the end of a string
 * @ch: the character to insert
 * @str: the string to work with
 *Return: new buffer or NULL
 */
char *put_char(char *str, char ch)
{
	int i = 0, len;
	char *buf;

	len = _strlen(str);
	buf = malloc(len + 2);
	if (buf == NULL)
	{
		free(buf);
		return (NULL);
	}
	buf = _strcpy(buf, str);
	while (buf != NULL)
	{
		if (*(buf + i) == '\0')
		{
			*(buf + i) = ch;
			*(buf + i + 1) = '\0';
			return (buf);
		}
		i++;
	}
	return (NULL);
}
