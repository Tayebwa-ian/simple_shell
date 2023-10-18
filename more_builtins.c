#include "shell.h"

/**
 * show_history - Display history to the shell on the stdout
 * @c:Parsed Command
 * @s:Statue Of Last Excute
 * Return: 0 Succes -1 Fail
 */
int show_history(__attribute__((unused))char **c, __attribute__((unused))int s)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		er = _itoa(counter);
		PRINTER(er);
		free(er);
		PRINTER(" ");
		PRINTER(line);

	}
	if (line)
		free(line);
	fclose(fp);
	return (0);
}
/**
 * execute_cmd - a command
 * @cmd: Parsed Command
 * Return: 0 Succes -1 Fail
 */
int execute_cmd(char **cmd)
{
	int status, check;
	pid_t pid;
	char *buff = NULL;

	if (*cmd == NULL)
	{
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}

	if (pid == 0)
	{
		if (_strncmp(*cmd, "./", 2) != 0 && _strncmp(*cmd, "/", 1) != 0)
		{
			buff = _getpath(cmd[0]);
			if (buff != NULL)
				cmd[0] = _strdup(buff);
		}
		check = execve(*cmd, cmd, environ);
		if (check == -1)
		{
			free(cmd);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	free(buff);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
/**
 * _setenv - function sets or change variable without setenv
 * @cmd: Parsed Command
 * @er: Statue Of Last Excute
 * Return: new value of the variable
 */
int _setenv(char **cmd, __attribute__((unused))int er)
{
	char *new_name = cmd[1];
	char *new_value = cmd[2];
	char *env_string = build(new_name, new_value, "=");

	if (_putenv(env_string) != 0)
	{
		free(env_string);
		return (0);
	}
	return (-1);
}
/**
 * _unsetenv - function removes the set environment variable
 * @cmd: Parsed Command
 * @er: Statue Last Command Excuted
 * Return: 0 on sucess otherwise -1
 */
int _unsetenv(char **cmd, __attribute__((unused))int er)
{
	char *new_name = cmd[1];
	int name_length = _strlen(new_name);
	int i, j;
	char end_char = '\0';

	if ((new_name == NULL) || (new_name[0] == end_char))
		return (-1);
	/* iterate throught the variables*/
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(new_name, environ[i], name_length) == 0)
		{
			/* shift all variables one value back*/
			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}
			return (0);
		}
	}
	return (-1);
}
