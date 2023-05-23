#include "shell.h"


/**
 * exec - execute a command
 * @argv: array of arguments
 */

void exec(char **argv)
{
	int process, stat;

	if (!argv || !argv[0])
		return;
	process = fork();
	if (process == -1)
	{
		perror(_get_env("_"));
	}
	if (process == 0)
	{
		execve(argv[0], argv, environ);
			perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	wait(&stat);
}

/**
 * _realloc - Reallocates memory block
 * @ptr: previous pointer
 * @old_size: old size of previous pointer
 * @new_size: new size for our pointer
 * Return: New resized Pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	char *old;

	unsigned int i;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(new_size);
	old = ptr;
	if (new == NULL)
		return (NULL);

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new[i] = old[i];
		free(ptr);
		for (i = old_size; i < new_size; i++)
			new[i] = '\0';
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			new[i] = old[i];
		free(ptr);
	}
	return (new);
}

/**
 * free_arv - frees the array of pointers arv
 *@arv: array of pointers
 */

void free_arv(char **arv)
{
	int i;

	for (i = 0; arv[i]; i++)
		free(arv[i]);
	free(arv);
}
