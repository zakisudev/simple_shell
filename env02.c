#include "shell.h"

/**
 * get_env - get environment variable as an array of strings
 * @inf: var
 * Return: 0
 */
char **get_env(inf_o *inf)
{
	if (!inf->environ || inf->env_ch)
	{
		inf->environ = lst_to_str(inf->env);
		inf->env_ch = 0;
	}

	return (inf->environ);
}

/**
 * unset_en_var - remove environment variable
 * @inf: var
 * @l: var
 * Return: 0
 */
int unset_en_var(inf_o *inf, char *l)
{
	lists_t *n = inf->env;
	size_t i = 0;
	char *k;

	if (!n || !l)
		return (0);

	while (n)
	{
		k = hay_need(n->str, l);
		if (k && *k == '=')
		{
			inf->env_ch = node_delete(&(inf->env), i);
			i = 0;
			n = inf->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (inf->env_ch);
}

/**
 * set_up_en_var - set or update environment variable
 * @inf: var
 * @l: var
 * @i: var
 * Return: 0
 */
int set_up_en_var(inf_o *inf, char *l, char *i)
{
	char *b = NULL;
	lists_t *n;
	char *k;

	if (!l || !i)
		return (0);

	b = malloc(_length_str(l) + _length_str(i) + 2);
	if (!b)
		return (1);
	_copy_string(b, l);
	_app_str(b, "=");
	_app_str(b, i);
	n = inf->env;
	while (n)
	{
		k = hay_need(n->str, l);
		if (k && *k == '=')
		{
			free(n->str);
			n->str = b;
			inf->env_ch = 1;
			return (0);
		}
		n = n->next;
	}
	add_beg_list(&(inf->env), b, 0);
	free(b);
	inf->env_ch = 1;
	return (0);
}

/**
 * penv_list - function for printing environment
 * @inf: var
 * Return: 0
 */
 int penv_list(inf_o *inf)
{
	lists_t *n = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_beg_list(&n, environ[j], 0);
	inf->env = n;
	return (0);
}
