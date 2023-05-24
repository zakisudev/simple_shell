#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>

int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
char *_str_dup(char *str);
char *_str_cnct(char *name, char *sep, char *value);

void(*_builtin_check(char **arv))(char **arv);
int _strtoint(char *s);
void handle_exit(char **arv);
char **tokenizer(char *str, const char *delim);
void exec(char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


extern char **environ;

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @p: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;


list_path *add_node_end(list_path **head, char *str);
list_path *link_path(char *path);
char *_where(char *filename, list_path *head);

/**
 * struct built_in - pointer to function with corresponding builtin command
 * @name: builtin command
 * @func: execute the builtin command
 */
typedef struct built_in
{
	char *name;
	void (*func)(char **);
} built_in;


void print_env(char **arv);
void _set_env(char **arv);
char *_get_env(const char *name);
void _unset_env(char **arv);

void free_arv(char **arv);
void free_list_t(list_path *head);


#endif /* SIMPLE_SHELL */

