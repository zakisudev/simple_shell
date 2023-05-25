#include "simple_shell.h"

/**
 * tokenizer - tokenizes input and stores it into an array
 * input_string: input to be parsed
 * @delim: delimiter to be used, needs to be one character string
 *
 * Return: array of tokens
 */

char **tokenizer(char *input_string, char *delim)
{
	int n_delim = 0;
	char **av = NULL;
	char *token = NULL;
	char *save_ptr = NULL;

	token = _strtok_r(input_string, delim, &save_ptr);

	while (token != NULL)
	{
		av = _realloc(av, sizeof(*av) * n_delim, sizeof(*av) * (n_delim + 1));
		av[n_delim] = token;
		token = _strtok_r(NULL, delim, &save_ptr);
		n_delim++;
	}

	av = _realloc(av, sizeof(*av) * n_delim, sizeof(*av) * (n_delim + 1));
	av[n_delim] = NULL;

	return (av);
}

/**
 *_stdout - prints a string to stdout
 *@string: string to be printed
 *@stream: stream to print out to
 *
 *Return: void, return nothing
 */
void _stdout(char *string, int stream)
{
	int i = 0;

	for (; string[i] != '\0'; i++)
		write(stream, &string[i], 1);
}

/**
 * _newline - removes new line from a string
 * @str: string to be used
 *
 *
 * Return: void
 */

void _newline(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	str[i] = '\0';
}

/**
 * __strcpy - copies a string to another buffer
 * @source: source to copy from
 * @destn: destination to copy to
 *
 * Return: void
 */

void __strcpy(char *source, char *destn)
{
	int i = 0;

	for (; source[i] != '\0'; i++)
		destn[i] = source[i];
	destn[i] = '\0';
}

/**
 * __strlen - counts string length
 * @str: string to be counted
 *
 * Return: length of the string
 */

int __strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (len);
	for (; str[len] != '\0'; len++)
		;
	return (len);
}
