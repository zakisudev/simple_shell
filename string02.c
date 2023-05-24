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
		inf->argv = str_tok1(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _duplicate_string(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		cmd_aliasing(inf);
		cmd_var_sub(inf);
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
			list_free(&(inf->env));
		if (inf->hist)
			list_free(&(inf->hist));
		if (inf->alias)
			list_free(&(inf->alias));
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
