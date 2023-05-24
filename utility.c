#include "shell.h"

/**
 * chained - check if command is chained
 * @inf: struct
 * @b: char var
 * @p: struct
 * Return: 1
 */
int chained(inf_o *inf, char *b, size_t *p)
{
	size_t i = *p;

	if (b[i] == '|' && b[i + 1] == '|')
	{
		b[i] = 0;
		i++;
		inf->cmdb_type = OR;
	}
	else if (b[i] == '&' && b[i + 1] == '&')
	{
		b[i] = 0;
		i++;
		inf->cmdb_type = AND;
	}
	else if (b[i] == ';')
	{
		b[i] = 0;
		inf->cmdb_type = CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * mod_chain - modify the command chained
 * @inf: struct
 * @b: char var
 * @p: struct
 * @i: struct
 * @l: struct
 */
void mod_chain(inf_o *inf, char *b, size_t *p, size_t i, size_t l)
{
	size_t k = *p;

	if (inf->cmdb_type == AND)
	{
		if (inf->stat)
		{
			b[i] = 0;
			k = l;
		}
	}
	if (inf->cmdb_type == OR)
	{
		if (!inf->stat)
		{
			b[i] = 0;
			k = l;
		}
	}

	*p = k;
}

/**
 * cmd_aliasing - handle aliasing
 * @inf: struct
 * Return: 1
 */
int cmd_aliasing(inf_o *inf)
{
	int j = 0;
	lists_t *n;
	char *p;

	for (j = 0; j < 10; j++)
	{
		n = prenode(inf->alias, inf->argv[0], '=');
		if (!n)
			return (0);
		free(inf->argv[0]);
		p = _str_srch(n->str, '=');
		if (!p)
			return (0);
		p = _duplicate_string(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * cmd_var_sub - substitute command variables
 * @inf: struct
 * Return: 0
 */
int cmd_var_sub(inf_o *inf)
{
	int i = 0;

	lists_t *n;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_compare_str(inf->argv[i], "$?"))
		{
			replace_str(&(inf->argv[i]),
				_duplicate_string(long_to_str(inf->stat, 10, 0)));
			continue;
		}
		if (!_compare_str(inf->argv[i], "$$"))
		{
			replace_str(&(inf->argv[i]),
				_duplicate_string(long_to_str(getpid(), 10, 0)));
			continue;
		}
		n = prenode(inf->env, &inf->argv[i][1], '=');
		if (n)
		{
			replace_str(&(inf->argv[i]),
				_duplicate_string(_str_srch(n->str, '=') + 1));
			continue;
		}
		replace_str(&inf->argv[i], _duplicate_string(""));
	}
	return (0);
}

/**
 * replace_str - replace string with another string
 * @o: char
 * @n: char
 * Return: 1
 */
int replace_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
