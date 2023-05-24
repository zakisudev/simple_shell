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
		x = _eatoi(inf->argv[1]);
		if (x == -1)
		{
			inf->stat = 2;
			p_err(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_n = _eatoi(inf->argv[1]);
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
		_puts("TODO: >>getcd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		d = get_env_var(inf, "HOME=");
		if (!d)
			r = /* TODO: what should this be? */
				chdir((d = get_env_var(inf, "PWD=")) ? d : "/");
		else
			r = chdir(d);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!get_env_var(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env_var(inf, "OLDPWD=")), _putchar('\n');
		r = /* TODO: what should this be? */
			chdir((d = get_env_var(inf, "OLDPWD=")) ? d : "/");
	}
	else
		r = chdir(inf->argv[1]);
	if (r == -1)
	{
		p_err(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		set_up_env_var(inf, "OLDPWD", get_env_var(inf, "PWD="));
		set_up_env_var(inf, "PWD", getcwd(b, 1024));
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
 * str_srch - search specific char in string
 * @s: var
 * @c: var
 * Return: NULL
 */
char *str_srch(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
