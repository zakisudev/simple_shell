#include "shell.h"

/**
 * env_wrapper - prints the environment variable
 * @inf: var
 * Return: 0
 */
int env_wrapper(inf_o *inf)
{
	pstr_list(inf->env);
	return (0);
}
/**
 * get_env_var - get the value of the environment variable
 * @inf: var
 * @name: var
 * Return: NULL
 */
char *get_env_var(inf_o *inf, const char *name)
{
	lists_t *n = inf->env;
	char *p;

	while (n)
	{
		p = hay_need(n->str, name);
		if (p && *p)
			return (p);
		n = n->next;
	}
	return (NULL);
}

/**
 * set_env - set an environment variable from arguments
 * @inf: var
 * Return: 1
 */
int set_env(inf_o *inf)
{
	if (inf->argc != 3)
	{
		_puts_error("Incorrect number of arguments\n");
		return (1);
	}
	if (set_up_en_var(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env - remove environment variables from argument
 * @inf: var
 * Return: 0
 */
int unset_env(inf_o *inf)
{
	int j = 1;

	if (inf->argc == 1)
	{
		_put_errors("Too few arguments.\n");
		return (1);
	}
	while (j <= inf->argc)
	{
		unset_en_var(inf, inf->argv[j]);
		j++;
	}

	return (0);
}

/**
 * create_list_env - entry
 * @inf: var
 * Return: 0
 */
int create_list_env(inf_o *inf)
{
	lists_t *n = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_beg_list(&n, environ[j], 0);
	inf->env = n;
	return (0);
}
