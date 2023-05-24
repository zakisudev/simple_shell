#include "shell.h"

/**
 * initialize_info - clear or reset inf
 * @inf: var
 */
void initialize_info(inf_o *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * populate_info - initializes and populates inf
 * @inf: var
 * @v: var
 */
void populate_info(inf_o *inf, char **v)
{
	int i = 0;

	inf->fn = v[0];
	if (inf->arg)
	{
		inf->argv = strtok1(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		re_alias(inf);
		re_vars(inf);
	}
}

/**
 * info_free - free inf
 * @inf: var
 * @l: var
 */
void info_free(inf_o *inf, int l)
{
	ffr(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (l)
	{
		if (!inf->cmdb)
			free(inf->arg);
		if (inf->env)
			fr_list(&(inf->env));
		if (inf->hist)
			fr_list(&(inf->hist));
		if (inf->alias)
			fr_list(&(inf->alias));
		ffr(inf->environ);
			inf->environ = NULL;
		block_free((void **)inf->cmdb);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUFSH);
	}
}

/**
 * block_free - free block of memory
 * @p: var
 * Return: 0
 */
int block_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
