#include "shell.h"

/**
 * pnt_lnk_lst - print content of linked list
 * @inf: var
 * Return: 0
 */
int pnt_lnk_lst(inf_o *inf)
{
	pnt_list_struct(inf->hist);
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

	p = _str_srch(s, '=');
	if (!p)
		return (1);
	i = *p;
	*p = 0;
	t = node_delete(&(inf->alias),
		get_node(inf->alias, prenode(inf->alias, s, -1)));
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

	p = _str_srch(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (rm_aliases(inf, s));

	cmd_aliasing(inf, s);
	return (add_beg_list(&(inf->alias), s, 0) == NULL);
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
		p = _str_srch(n->str, '=');
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
		p = _str_srch(inf->argv[j], '=');
		if (p)
			create_aliases(inf, inf->argv[j]);
		else
			pnt_alias(prenode(inf->alias, inf->argv[j], '='));
	}

	return (0);
}
