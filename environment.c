#include "shell.h"

/**
 * print_env - prints the current environment
 * @arv: array of arguments
 */
void print_env(char **arv __attribute__ ((unused)))
{

	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}

}

/**
 * _set_env - Initialize a new environment variable, or modify an existing one
 * @arv: array of entered words
 */
void _set_env(char **arv)
{
	int i, j, k;

	if (!arv[1] || !arv[2])
	{
		perror(_get_env("_"));
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (arv[1][j] == environ[i][j])
		{
			while (arv[1][j])
			{
				if (arv[1][j] != environ[i][j])
					break;

				j++;
			}
			if (arv[1][j] == '\0')
			{
				k = 0;
				while (arv[2][k])
				{
					environ[i][j + 1 + k] = arv[2][k];
					k++;
				}
				environ[i][j + 1 + k] = '\0';
				return;
			}
		}
	}
	if (!environ[i])
	{

		environ[i] = _str_cnct(arv[1], "=", arv[2]);
		environ[i + 1] = NULL;

	}
}

/**
 * _get_env - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_get_env(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}
	return (0);
}

/**
 * _unset_env - Remove an environment variable
 * @arv: array of entered words
 */
void _unset_env(char **arv)
{
	int i, j;

	if (!arv[1])
	{
		perror(_get_env("_"));
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (arv[1][j] == environ[i][j])
		{
			while (arv[1][j])
			{
				if (arv[1][j] != environ[i][j])
					break;

				j++;
			}
			if (arv[1][j] == '\0')
			{
				free(environ[i]);
				environ[i] = environ[i + 1];
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				return;
			}
		}
	}
}
