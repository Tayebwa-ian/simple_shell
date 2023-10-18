#include "shell.h"
/**
 * exit_cmd - handle exit shell command
 * @cmd: Parsed Command
 * @input: User Input
 * @argv:Program Name
 * @c:Excute Count
 * Return: Void (Exit Statue)
 */
void  exit_cmd(char **cmd, char *input, char **argv, int c)
{
	int statue, i = 0;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) != 0)
		{
			_prerror(argv, c, cmd);
			break;
		}
		else
		{
			statue = _atoi(cmd[1]);
			free(input);
			free(cmd);
			exit(statue);
		}
	}
}


/**
 * change_dir - Change Dirctorie
 * @cmd: Parsed Command
 * @er: Statue Last Command Excuted
 * Return: 0 Success 1 Failed (For Old Pwd Always 0 Case No Old PWD)
 */
int change_dir(char **cmd, __attribute__((unused))int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		value = chdir(_getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		value = chdir(_getenv("OLDPWD"));
	}
	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", _getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
/**
 * list_env - Display Enviroment Variables
 * @cmd:Parsed Command
 * @er:Statue of Last command Excuted
 * Return:Always 0
 */
int list_env(__attribute__((unused)) char **cmd,
	     __attribute__((unused)) int er)
{
	size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * show_help - show help For Builtin commands
 * @cmd:Parsed Command
 * @er: Statue Of Last Command Excuted
 * Return: 0 Succes -1 Fail
 */
int show_help(char **cmd, __attribute__((unused))int er)
{
	int fd, w, rd = 1;
	char c, *tmp;

	tmp = malloc(20);
	tmp = _strcat(tmp, "help_files/");
	tmp = _strcat(tmp, cmd[1]);
	fd = open(tmp, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		free(tmp);
		return (0);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		w = write(STDOUT_FILENO, &c, rd);
		if (w < 0)
		{
			free(tmp);
			return (-1);
		}
	}
	_putchar('\n');
	free(tmp);
	return (0);
}
/**
 * echo_cmd - implemented echo builtin command
 * @er:Statue Of Last Command Excuted
 * @cmd: Parsed Command
 * Return: Always 0 Or Excute Normal Echo
 */
int echo_cmd(char **cmd, int er)
{
	char *path;
	unsigned int  pid = getppid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		print_number(er);
		PRINTER("\n");
	}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINTER("\n");

	}
	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");

	}
	else
		return (execute_cmd(cmd));

	return (1);
}
