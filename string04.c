#include "shell.h"

/**
 * _length_str - preints the lengt of a string
 * @s: char
 * Return: j
 */
int _length_str(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _compare_str - compares string s1 with s2
 * @s1: string 1
 * @s2: string 2
 * Return: 1 or -1
 */
int _compare_str(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * hay_need - checks if hay starts with need
 * @hay: char
 * @need: char
 * Return: haystack
 */
char *hay_need(const char *hay, const char *need)
{
	while (*need)
		if (*need++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * _app_str - appends two strings
 * @dest: char var
 * @src: char var
 * Return: ret
 */
char *_app_str(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * build_path - build the full path for an executable
 * @directory: directory in PATH
 * @command: command name
 * Return: full path or NULL if memory allocation fails
 */
char *build_path(char *dir, char *comm)
{
	size_t directory_len = strlen(dir);
	size_t command_len = strlen(comm);
	char *path = malloc(directory_len + command_len + 2);

	if (!path)
		return NULL;
	strcpy(path, dir);
	path[directory_len] = '/';
	strcpy(path + directory_len + 1, comm);
	path[directory_len + command_len + 1] = '\0';
	return path;
}
