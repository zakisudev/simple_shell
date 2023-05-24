#include "shell.h"

/**
 * _puts_error - prints error to the standard error
 * @s: char var
 */
void _puts_error(char *s)
{
	int i = 0;

	if (!s)
		return;
	for (i = 0; s[i] != '\0'; i++)
		_put_error_char(s[i]);
}

/**
 * _put_error_char - prints a char to the standard error
 * @c: char var
 * Return: 1
 */
int _put_error_char(char c)
{
	static int i;
	static char b[WB_SIZE];

	if (c == BUFSH || i >= WB_SIZE)
	{
		write(2, b, i);
		i = 0;
	}
	if (c != BUFSH)
		b[i++] = c;
	return (1);
}

/**
 * _put_error_char_fd - prints a char to a file descriptor
 * @c: char var
 * @f: int var
 * Return: 1
 */
int _put_error_char_fd(char c, int f)
{
	static int i;
	static char b[WB_SIZE];

	if (c == BUFSH || i >= WB_SIZE)
	{
		write(f, b, i);
		i = 0;
	}
	if (c != BUFSH)
		b[i++] = c;
	return (1);
}

/**
 * _put_errors_fd - prints error to a file descriptor
 * @s: char var
 * @f: int var
 * Return: i
 */
int _put_errors_fd(char *s, int f)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _put_error_char_fd(*s++, f);
	}
	return (i);
}
