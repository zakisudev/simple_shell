#include "shell.h"

/**
 * is_interactive - check whether interactive
 * @inf: struct
 * Return: func
 */
int is_interactive(inf_o *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delim - check is c is delimeter
 * @c: char var
 * @l: char l
 * Return: 0
 */
int is_delim(char c, char *l)
{
	while (*l)
		if (*l++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - check if c is char
 * @c: var
 * Return: 0
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert string to integer
 * @s: char var
 * Return: t
 */
int _atoi(char *s)
{
	int i, n = 1, f = 0, t;
	unsigned int r = 0;

	for (i = 0;  s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			n *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			r *= 10;
			r += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (n == -1)
		t = -r;
	else
		t = r;

	return (t);
}
