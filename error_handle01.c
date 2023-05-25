#include "shell.h"

/**
 * _str_to_int - converts string to integer
 * @str: string
 * Return: l or -1 on error
 */
int _str_to_int(char *str)
{
	int i = 0;
	int sign = 1;
	unsigned long int l = 0;

	if (str == NULL)
		return (-1);

	while (str[i] == ' ' || str[i] == '\t')
		i++;

	if (str[i] == '+')
	{
		i++;
	}
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}

	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			l *= 10;
			l += (str[i] - '0');
			if (l > INT_MAX)
			return (-1);
		}
		else
		{
			return (-1);
		}
		i++;
	}
	return ((int)(l * sign));
}

/**
 * error_pnt - prints an error to the standard output
 * @inf: struct
 * @str: string
 */
void error_pnt(inf_o *inf, char *str)
{
	_puts_error(inf->fn);
	_puts_error(": ");
	int_pnt(inf->lcount, STDERR_FILENO);
	_puts_error(": ");
	_puts_error(inf->argv[0]);
	_puts_error(": ");
	_puts_error(str);
}

/**
 * int_pnt - prints an integer to standard error
 * @in: int var
 * @f: int var
 * Return: j
 */
int int_pnt(int in, int f)
{
	int (*__putchar)(char) = _putchar;
	int i, j = 0;
	unsigned int s, cr;

	if (f == STDERR_FILENO)
		__putchar = _put_error_char;
	if (in < 0)
	{
		s = -in;
		__putchar('-');
		j++;
	}
	else
		s = in;
	cr = s;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (s / i)
		{
			__putchar('0' + cr / i);
			j++;
		}
		cr %= i;
	}
	__putchar('0' + cr);
	j++;

	return (j);
}

/**
 * long_to_str - convert long integer to str
 * @m: int var
 * @bs: buf
 * @f: int var
 * Return: p
 */
char *long_to_str(long int m, int bs, int f)
{
	static char *r;
	static char b[50];
	char s = 0;
	char *p;
	unsigned long n = m;

	if (!(f & CONV_UNSIGN) && m < 0)
	{
		n = -m;
		s = '-';

	}
	r = f & CONV_LOW ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &b[49];
	*p = '\0';

	do	{
		*--p = r[n % bs];
		n /= bs;
	} while (n != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * comment_rm - removes comments from strings
 * @b: char var
 */
void comment_rm(char *b)
{
	int i = 0;

	while (b[i] != '\0')
	{
		if (b[i] == '#' && (!i || b[i - 1] == ' '))
		{
			b[i] = '\0';
			break;
		}
		i++;
	}
}
