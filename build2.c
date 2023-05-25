#include "shell.h"

/**
 * eexit - handle exit command
 * @inf: var
 * Return: -2
 */
int eexit(inf_o *inf)
{
	int x;

	if (inf->argv[1])
	{
		x = _str_to_int(inf->argv[1]);
		if (x == -1)
		{
			inf->stat = 2;
			error_pnt(inf, "Illegal number: ");
			_puts_error(inf->argv[1]);
			_put_error_char('\n');
			return (1);
		}
		inf->err_n = _str_to_int(inf->argv[1]);
		return (-2);
	}
	inf->err_n = -1;
	return (-2);
}

/**
 * handle_cd - handle the cd command
 * @inf: var
 * Return: 0
 */
int handle_cd(inf_o *inf)
{
	char *s, *d, b[1024];
	int r;

	s = getcwd(b, 1024);
	if (!s)
		_puts("ERROR\n");

	if (!inf->argv[1])
	{
		d = get_env_var(inf, "HOME=");
		if (!d)
			d = get_env_var(inf, "PWD=");
		if (!d)
			d = "/";
		r = chdir(d);
	}
	else if (_compare_str(inf->argv[1], "-") == 0)
	{
		d = get_env_var(inf, "OLDPWD=");
		if (!d)
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(d);
		_putchar('\n');
		r = chdir(d);
	}
	else
		r = chdir(inf->argv[1]);

	if (r == -1)
	{
		error_pnt(inf, "can't cd to ");
		_puts_error(inf->argv[1]), _put_error_char('\n');
	}
	else
	{
		set_up_en_var(inf, "OLDPWD", get_env_var(inf, "PWD="));
		set_up_en_var(inf, "PWD", getcwd(b, 1024));
	}
	return (0);
}

/**
 * handle_help - handles help
 * @inf: var
 * Return: 0
 */
int handle_help(inf_o *inf)
{
	char **i;

	i = inf->argv;
	_puts("Shell Help:\n");
	_puts("============\n");
	_puts("This is a simple shell program.\n");
	_puts("Supported commands:\n");
	_puts("- cd [directory]: Change current directory.\n");
	_puts("- ls: List files and directories in the current directory.\n");
	_puts("- help: Display help information.\n");
	_puts("- exit: Exit the shell.\n");
	if (0)
		_puts(*i);
	return (0);
}

/**
 * _str_srch - search specific char in string
 * @s: var
 * @c: var
 * Return: NULL
 */
char *_str_srch(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
