#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/*helpers*/
void _stdout(char *, int);
char **tokenizer(char *, char *);
void _newline(char *);
int __strlen(char *);
void __strcpy(char *, char *);

/*helpers2*/
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);

/*helpers3*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int, unsigned int);
void ctrl_c_handler(int);
void remove_comment(char *);

/*utils*/
int get_cmd(char *);
void execcmd(char **, int);
char *check_path(char *);
void (*parse_func(char *))(char **);
char *_getenv(char *);

/*built_in*/
void p_env(char **);
void eexit(char **);

/*main*/
extern void is_noninteractive(void);
extern void commander(char **, int);

#endif /*SHELL_H*/


