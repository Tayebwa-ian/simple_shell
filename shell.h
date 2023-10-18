#ifndef _SHELL_H_
#define _SHELL_H_

/* environ var */

extern char **environ;

/* MACROS */

#define BUFSIZE 1024
#define PRINTER(c) (write(STDOUT_FILENO, c, _strlen(c)))

/* LIBS USED */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>


/**
 * struct bulltin - contain bultin to handle and function to excute
 * @command:pointer to char
 * @fun:fun to excute when bultin true
 */

typedef struct  bulltin
{
	char *command;
	int (*fun)(char **line, int er);
} bul_t;

/* builtin.c */
void  exit_cmd(char **cmd, char *input, char **argv, int c);
int change_dir(char **cmd, int er);
int list_env(char **cmd, int er);
int show_help(char **cmd, int er);
int echo_cmd(char **cmd, int er);

/* even_more_strings.c */
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(char *str);

/* getline.c */
char *_getline(int n, int fd);
char *resize(int *n, char *buf);
void hashtag_handle(char *buff);
void space_handle(char *str);
char *handle_line(char *buffer, int n);

/* history.c */
int history(char *input);
void free_env(char **env);

/* memory_mgt.c */
void free_all(char **cmd, char *line);
void *_realloc(void *previous, int n, int m);
void _memcpy(void *new, void *old, int n);
void *fill_an_array(void *a, int el, unsigned int len);
void *_calloc(unsigned int size);

/* more_bultins.c */
int show_history(char **c, int s);
int execute_cmd(char **cmd);
int _setenv(char **cmd, int er);
int _unsetenv(char **cmd, int er);

/* more_strings.c */
int _strcmp(char *s1, char *s2);
int _isalpha(int c);
char *_itoa(unsigned int n);
void array_rev(char *arr, int len);
int intlen(int num);

/* more_utils.c */
char **get_tokens(char *input);
int _putenv(char *var);
int environ_size(void);
void chain_cmds(char *input, int counter, char **argv, char *ch);
char *put_char(char *str, char ch);

/* path.c */
char *_getpath(char *cmd);
char *build(char *token, char *cmd, char *ch);
char *_getenv(char *name);

/* printer.c */
void print_number(int n);
void prompt(void);
void print_error(char *input, int counter, char **argv);
void _prerror(char **argv, int c, char **cmd);

/* shell.c */
int main(int argc, char **argv);
int check_builtin(char **cmd);
void handle_sig(int sig);

/* str_tok.c */
char *_strtok(char *str, char *delim, char **save_point);
char *get_delim(char *str, char *delim);
char *_strtok2(char *str, char **save_point);
char *get_delim2(char *str);

/* string.c */
int _putchar(char c);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
int _atoi(char *s);
void _puts(char *str);

/* utils.c */
int handle_builtin(char **cmd, int er);
void read_file(char *filename, char **argv);
void handle_files(char *line, int counter, FILE *fd, char **argv);
void exit_for_file(char **cmd, char *line, FILE *fd);
int run_cmd(char **cmd, char *input, int c, char **argv);

#endif
