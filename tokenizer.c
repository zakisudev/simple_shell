#include "shell.h"


/**
 * tokenizer - splits a string input to an array of pointers of words
 * @str: the string input to be split
 * @delim: the delimiter
 * Return: array of pointers to words
 */

char **tokenizer(char *str, const char *delim)
{
	int i, num_word;
	char **ptr_array;
	char *token;
	char *dest;

	dest = malloc(_strlen(str) + 1);
	if (dest == NULL)
	{
		perror(_get_env("_"));
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';

	token = strtok(dest, delim);
	ptr_array = malloc((sizeof(char *) * 2));
	ptr_array[0] = _str_dup(token);

	i = 1;
	num_word = 3;
	while (token)
	{
		token = strtok(NULL, delim);
		ptr_array = _realloc(ptr_array, (sizeof(char *) *
		(num_word - 1)), (sizeof(char *) * num_word));
		ptr_array[i] = _str_dup(token);
		i++;
		num_word++;
	}
	free(dest);
	return (ptr_array);
}
