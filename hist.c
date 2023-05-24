#include "shell.h"

/**
 * hist_path - construct the path to history
 * @inf: struct
 * Return: b
 */
char *hist_path(inf_o *inf)
{
	char *b, *d;

	d = get_env_var(inf, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_length_str(d) + _length_str(H_F) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_copy_string(b, d);
	_app_str(b, "/");
	_app_str(b, H_F);
	return (b);
}

/**
 * hist_file - writes a history to a file
 * @inf: struct
 * Return: 1
 */
int hist_file(inf_o *inf)
{
	ssize_t f;
	char *fname = hist_path(inf);
	lists_t *n = NULL;

	if (!fname)
		return (-1);

	f = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (f == -1)
		return (-1);
	for (n = inf->hist; n; n = n->next)
	{
		_put_errors_fd(n->str, f);
		_put_error_char_fd('\n', f);
	}
	_put_error_char_fd(BUFSH, f);
	close(f);
	return (1);
}

/**
 * read_hist_file - read command history from a file
 * @inf: struct
 * Return: inf
 */
int read_hist_file(inf_o *inf)
{
	int i, l = 0, lc = 0;
	ssize_t f, rlen, fs = 0;
	struct stat s;
	char *b = NULL, *fname = hist_path(inf);

	if (!fname)
		return (0);

	f = open(fname, O_RDONLY);
	free(fname);
	if (f == -1)
		return (0);
	if (!fstat(f, &s))
		fs = s.st_size;
	if (fs < 2)
		return (0);
	b = malloc(sizeof(char) * (fs + 1));
	if (!b)
		return (0);
	rlen = read(f, b, fs);
	b[fs] = 0;
	if (rlen <= 0)
		return (free(b), 0);
	close(f);
	for (i = 0; i < fs; i++)
		if (b[i] == '\n')
		{
			b[i] = 0;
			add_hist_file(inf, b + l, lc++);
			l = i + 1;
		}
	if (l != i)
		add_hist_file(inf, b + l, lc++);
	free(b);
	inf->hcount = lc;
	while (inf->hcount-- >= H_M)
		node_delete(&(inf->hist), 0);
	as_hist_file(inf);
	return (inf->hcount);
}

/**
 * add_hist_link - add history to the link list
 * @inf: struct
 * @b: char var
 * @lc: int var
 * Return: 0
 */
int add_hist_file(inf_o *inf, char *b, int lc)
{
	lists_t *n = NULL;

	if (inf->hist)
		n = inf->hist;
	add_beg_list(&n, b, lc);

	if (!inf->hist)
		inf->hist = n;
	return (0);
}

/**
 * as_hist_file - reassign history list
 * @inf: struct
 * Return: inf
 */
int as_hist_file(inf_o *inf)
{
	lists_t *n = inf->hist;
	int i = 0;

	while (n)
	{
		n->n = i++;
		n = n->next;
	}
	return (inf->hcount = i);
}
