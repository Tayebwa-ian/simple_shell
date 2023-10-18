#include "shell.h"

/**
 * main - Simple Shell (Hsh)
 * @argc: Argument Count
 * @argv:Argument Value
 * Return: Exit Value By Status
 */

int main(__attribute__((unused)) int argc, char **argv)
{
	char *input = NULL, **cmd, *ch;
	int counter = 0, statue = 1, st = 0, n = 0;

	if (argv[1] != NULL)
		read_file(argv[1], argv);
	signal(SIGINT, handle_sig);
	while (statue)
	{
		counter++;
		if (isatty(STDIN_FILENO))
			prompt();
		input = _getline(n, 0);
		if (input[0] == '\0')
			continue;
		history(input);
		ch = get_delim2(input);
		if (ch != NULL && *ch != '\n')
		{
			chain_cmds(input, counter, argv, ch);
			free(input);
			continue;
		}
		cmd = get_tokens(input);
		if (_strcmp(cmd[0], "exit") == 0)
			exit_cmd(cmd, input, argv, counter);
		else if (check_builtin(cmd) == 0)
		{
			st = handle_builtin(cmd, st);
			free_all(cmd, input);
			continue;
		}
		else
		{
			st = run_cmd(cmd, input, counter, argv);

		}
		free_all(cmd, input);
	}
	return (statue);
}
/**
 * check_builtin - check builtin
 *
 * @cmd:command to check
 * Return: 0 Succes -1 Fail
 */
int check_builtin(char **cmd)
{
	bul_t fun[] = {
		{"cd", NULL},
		{"help", NULL},
		{"echo", NULL},
		{"history", NULL},
		{"setenv", NULL},
		{"unsetenv", NULL},
		{NULL, NULL}
	};
	int i = 0;
		if (*cmd == NULL)
	{
		return (-1);
	}

	while ((fun + i)->command)
	{
		if (_strcmp(cmd[0], (fun + i)->command) == 0)
			return (0);
		i++;
	}
	return (-1);
}

/**
 * handle_sig - Handle ^C
 * @sig:Captured Signal
 * Return: Void
 */
void handle_sig(int sig)
{
	if (sig == SIGINT)
		PRINTER("\n$ ");
}
