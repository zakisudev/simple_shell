#include "shell.h"

/**
 * len_lst - determines length of linked list
 * @head: struct
 * Return: j
 */
size_t len_lst(const lists_t *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * lst_to_str - convert linked list strings to array of strings
 * @head: struct
 * Return: array of strings
 */
char **lst_to_str(lists_t *head)
{
	lists_t *n = head;
	size_t i = len_lst(head), k;
	char **tr;
	char *st;

	if (!head || !i)
		return (NULL);
	tr = malloc(sizeof(char *) * (i + 1));
	if (!tr)
		return (NULL);
	for (i = 0; n; n = n->next, i++)
	{
		st = malloc(_length_str(n->str) + 1);
		if (!st)
		{
			for (k = 0; k < i; k++)
				free(tr[i]);
			free(tr);
			return (NULL);
		}

		st = _copy_string(st, n->str);
		tr[i] = st;
	}
	tr[i] = NULL;
	return (tr);
}

/**
 * pnt_list_struct - print list of struct
 * @head: struct
 * Return: j
 */
size_t pnt_list_struct(const lists_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(long_to_str(head->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * prenode - search for a node that starts with char
 * @n: struct
 * @pre: char
 * @c: char
 * Return: NULL
 */
lists_t *prenode(lists_t *n, char *pre, char c)
{
	char *p = NULL;

	while (n)
	{
		p = hay_need(n->str, pre);
		if (p && ((c == -1) || (*p == c)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * get_node - get node at the i location
 * @head: struct
 * @n: struct
 * Return: -1
 */
ssize_t get_node(lists_t *head, lists_t *n)
{
	size_t j = 0;

	while (head)
	{
		if (head == n)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
