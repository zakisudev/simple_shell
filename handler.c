#include "shell.h"

/**
* _builtin_check - checks if the command is a builtin
* @arv: array of arguments
* Return: pointer to function that takes arv and returns void
*/
void(*_builtin_check(char **arv))(char **arv)
{
	int i, j;
	built_in T[] = {
		{"exit", handle_exit},
		{"env", print_env},
		{"setenv", _set_env},
		{"unsetenv", _unset_env},
		{NULL, NULL}
	};

	for (i = 0; T[i].name; i++)
	{
		j = 0;
		if (T[i].name[j] == arv[0][j])
		{
			for (j = 0; arv[0][j]; j++)
			{
				if (T[i].name[j] != arv[0][j])
					break;
			}
			if (!arv[0][j])
				return (T[i].func);
		}
	}
	return (0);
}

/**
 * handle_exit - exits the shell with or without a return of status number
 * @arv: array of words of the entered line
 */
void handle_exit(char **arv)
{
	int i, num;

	if (arv[1])
	{
		num = _strtoint(arv[1]);
		if (num <= -1)
			num = 2;
		free_arv(arv);
		exit(num);
	}
	for (i = 0; arv[i]; i++)
		free(arv[i]);
	free(arv);
	exit(0);
}

/**
 * _strtoint - converts a string into an integer
 * @s: pointer to a string
 * Return: the integer
 */
int _strtoint(char *s)
{
	int i, intgr, sign = 1;

	i = 0;
	intgr = 0;
	while (!((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
	{
		if (s[i] == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		intgr = (intgr * 10) + (sign * (s[i] - '0'));
		i++;
	}
	return (intgr);
}
