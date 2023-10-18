#include "shell.h"

/**
 * handle_builtin - Handle Builtin Command
 * @cmd: Parsed Command
 * @er:statue of last Excute
 * Return: -1 Fail 0 Succes (Return :Excute Builtin)
 */

int handle_builtin(char **cmd, int er)
{
	 bul_t bil[] = {
		{"cd", change_dir},
		{"env", list_env},
		{"help", show_help},
		{"echo", echo_cmd},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"history", show_history},
		{NULL, NULL}
	};
	int i = 0;

	while ((bil + i)->command)
	{
		if (_strcmp(cmd[0], (bil + i)->command) == 0)
		{
			return ((bil + i)->fun(cmd, er));
		}
		i++;
	}
	return (-1);
}

/**
 * read_file - Read Command From File
 * @filename:Filename
 * @argv:Program Name
 * Return: -1 or  0
 */

void read_file(char *filename, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		handle_files(line, counter, fp, argv);

	}
	if (line)
		free(line);
	fclose(fp);
	exit(0);
}
/**
 * handle_files - run commands from a given file
 * @line: Line From A File
 * @counter:Error Counter
 * @fd:File Descriptor
 * @argv:Program Name
 * Return : Excute A line void
 */
void handle_files(char *line, int counter, FILE *fd, char **argv)
{
	char **cmd, *ch;
	int st = 0;

	ch = get_delim2(line);
	if (ch != NULL && *ch != '\n')
	{
		chain_cmds(line, counter, argv, ch);
		return;
	}

	cmd = get_tokens(line);
	if (_strncmp(cmd[0], "exit", 4) == 0)
	{
		exit_for_file(cmd, line, fd);
	}
	else if (check_builtin(cmd) == 0)
	{
		st = handle_builtin(cmd, st);
		free(cmd);
	}
	else
	{
		st = run_cmd(cmd, line, counter, argv);
		free(cmd);
	}
}
/**
 * exit_for_file - Exit Shell when working with a File
 * @line: Line From A File
 * @cmd: Parsed Command
 * @fd:File Descriptor
 * Return : Case Of Exit in A File Line
 */
void exit_for_file(char **cmd, char *line, FILE *fd)
{
	int statue, i = 0;

	if (cmd[1] == NULL)
	{
		free(line);
		free(cmd);
		fclose(fd);
		exit(errno);
	}
	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) < 0)
		{
			perror("illegal number");
		}
	}
	statue = _atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(statue);
}

/**
 * run_cmd - Excutes command if it exists
 *
 * @cmd:Parsed Command
 * @input: input from stdin or a file
 * @c:Shell Excution Time Case of Command Not Found
 * @argv:Program Name
 * Return: 1 Case Command Null -1 Wrong Command 0 Command Excuted
 */
int run_cmd(char **cmd, char *input, int c, char **argv)
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
			print_error(cmd[0], c, argv);
			free_all(cmd, input);
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
