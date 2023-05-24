#include "shell.h"

/**
 * pnt_lnk_lst - print content of linked list
 * @inf: var
 * Return: 0
 */
int pnt_lnk_lst(inf_o *inf)
{
	p_list(inf->hist);
	return (0);
}

/**
 * rm_aliases - remove an alias from linked list of aliases
 * @inf: var
 * @s: var
 * Return: 0
 */
int rm_aliases(inf_o *inf, char *s)
{
	char *p, i;
	int t;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	i = *p;
	*p = 0;
	t = delete_node_at_i(&(inf->alias),
		get_node_i(inf->alias, node_starts_with(inf->alias, s, -1)));
	*p = i;
	return (t);
}

/**
 * create_aliases - create aliases in linked list of aliases
 * @inf: var
 * @s: var
 * Return: 0
 */
int create_aliases(inf_o *inf, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (rm_aliases(inf, s));

	re_aliases(inf, s);
	return (add_node_end(&(inf->alias), s, 0) == NULL);
}

/**
 * pnt_alias - print contents of an alias stored in a node
 * @n: var
 * Return: 1
 */
int pnt_alias(lists_t *n)
{
	char *p = NULL, *s = NULL;

	if (n)
	{
		p = _strchr(n->str, '=');
		for (s = n->str; s <= p; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mng_alias - handles the management of an alias
 * @inf: var
 * Return: 0
 */
int mng_alias(inf_o *inf)
{
	int j = 0;
	char *p = NULL;
	lists_t *n = NULL;

	if (inf->argc == 1)
	{
		n = inf->alias;
		while (n)
		{
			pnt_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		p = _strchr(inf->argv[j], '=');
		if (p)
			create_aliases(inf, inf->argv[j]);
		else
			pnt_alias(node_starts_with(inf->alias, inf->argv[j], '='));
	}

	return (0);
}
