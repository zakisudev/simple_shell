#include "shell.h"

/**
 * command_valid - checks if the command os valid
 * @inf: var
 * @p: var
 * Return: 0
 */
int command_valid(inf_o *inf, char *p)
{
	struct stat t;

	(void)inf;
	if (!p || stat(p, &t))
		return (0);

	if (t.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * get_substr - get substring from a given string
 * @p: string pointer
 * @s: starting index of the substring
 * @st: ending index of the substring
 * Return: 0
 */
char *get_substr(char *p, int s, int st)
{
	static char b[1024];
	int j = 0, k = 0;

	for (k = 0, j = s; j < st; j++)
	{
		if (p[j] != ':')
			b[k++] = p[j];
	}
	b[k] = 0;
	return (b);
}

/**
 * cmd_executable - search for a command executable
 * @inf: a pointer to a structure
 * @ps: a string containing a colon
 * @c: commant to search for
 * Return: 0
 */
char *cmd_executable(inf_o *inf, char *ps, char *c)
{
	char *path_copy = _duplicate_string(ps);
	char *token = strtok(path_copy, ":");
	char *executable_path = build_path(token, c);

	if (!path_copy)
		return (NULL);

	while (token != NULL)
	{
		if (executable_path != NULL && access(executable_path, X_OK) == 0)
		{
			free(path_copy);
			return (executable_path);
		}
		if(command_valid(inf, path_copy))
			return(path_copy);
		free(executable_path);
		token = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * _str_cpy - copy string from src to dest
 * @dest: destination of string
 * @src: source of string
 * @n: var
 * Return: s
 */
char *_str_cpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		for (j = i; j < n; j++)
			dest[j] = '\0';
	}
	return (s);
}

/**
 * _str_n_cat - concatenate string
 * @dest: destination
 * @src: source
 * @n: var
 * Return: s
 */
char *_str_n_cat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
