#include "shell.h"

/**
 * buf_save - get and store input to buffer
 * @inf: struct
 * @b: char
 * @l: var
 * Return: s
 */
ssize_t buf_save(inf_o *inf, char **b, size_t *l)
{
	ssize_t s = 0;
	size_t ls = 0;

	if (!(*l))
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, sigint_handler);

		s = _getline(inf, b, &ls);
		if (s > 0)
		{
			if ((*b)[s - 1] == '\n')
			{
				(*b)[s - 1] = '\0';
				s--;
			}
			inf->lcount_f = 1;
			comment_rm(*b);
			add_hist_file(inf, *b, inf->hcount++);
			*l = s;
			inf->cmdb = b;
		}
	}
	return (s);
}

/**
 * filed_buff - reads from a fd to buffer
 * @inf: struct
 * @b: char
 * @i: var
 * Return: s
 */
ssize_t filed_buff(inf_o *inf, char *b, size_t *i)
{
	 ssize_t s = 0;

	if (*i)
		return (0);
	s = read(inf->readfd, b, RB_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _getline - read from standard input
 * @inf: struct
 * @pr: char
 * @l: var
 * Return: x
 */
int _getline(inf_o *inf, char **pr, size_t *l)
{
	 static char b[RB_SIZE];
	 static size_t i, ls;
	 size_t j;
	 ssize_t s = 0, x = 0;
	 char *p = NULL, *np = NULL, *c;

	 p = *pr;
	if (p && l)
		x = *l;
	if (i == ls)
		i = ls = 0;
	 s = filed_buff(inf, b, &ls);
	if (s == -1 || (s == 0 && ls == 0))
		return (-1);
	 c  = _str_srch(b + i, '\n');

	 j = c ? 1 + (unsigned int)(c - b) : ls;

	np = _realoc(p, x, x ? x + j : j + 1);
	if (!np)
		return (p ? free(p), -1 : -1);
	if (x)
		_str_n_cat(np, b + i, j + i);
	else
		_str_cpy(np, b + i, j - i + 1);

	x += j - i;
	i = j;
	p = np;

	if (l)
		*l = x;
	*pr = p;
	return (x);
}

/**
 * sigint_handler - handles ctrl+c press
 * @si: signal
 */
void sigint_handler(__attribute__((unused))int si)
{
	 _puts("\n");
	 _puts("$ ");
	 _putchar (BUFSH);
}
