#include "shell.h"

/**
 * str_tok1 - replace strtok
 * @sr: var
 * @a: var
 * Return: v
 */
char **str_tok1(char *sr, char *a)
{
	int i, j, z, m, count = 0;
	char **v;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	if (!a)
		a = " ";
	for (i = 0; sr[i] != '\0'; i++)
		if (!is_delim(sr[i], a) && (is_delim(sr[i + 1], a) || !sr[i + 1]))
			count++;

	if (count == 0)
		return (NULL);
	v = malloc((1 + count) * sizeof(char *));
	if (!v)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (is_delim(sr[i], a))
			i++;
		z = 0;
		while (!is_delim(sr[i + z], a) && sr[i + z])
			z++;
		v[j] = malloc((z + 1) * sizeof(char));
		if (!v[j])
		{
			for (z = 0; z < j; z++)
				free(v[z]);
			free(v);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			v[j][m] = sr[i++];
		v[j][m] = 0;
	}
	v[j] = NULL;
	return (v);
}

/**
 * str_tok2 - replace strtok
 * @sr: var
 * @a: var
 * Return: v
 */
char **str_tok2(char *sr, char a)
{
	int i, j, z, m, count = 0;
	char **v;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	i = 0;
	for (i = 0; sr[i] != '\0'; i++)
	{
		if ((sr[i] != a && sr[i + 1] == a) ||
		    (sr[i] != a && !sr[i + 1]) || sr[i + 1] == a)
			count++;
	}
	if (count == 0)
		return (NULL);
	v = malloc((1 + count) * sizeof(char *));
	if (!v)
		return (NULL);
	i = 0;
	j = 0;
	for (i = 0, j = 0; j < count; j++)
	{
		while (sr[i] == a && sr[i] != a)
			i++;
		z = 0;
		while (sr[i + z] != a && sr[i + z] && sr[i + z] != a)
			z++;
		v[j] = malloc((z + 1) * sizeof(char));
		if (!v[j])
		{
			for (z = 0; z < j; z++)
				free(v[z]);
			free(v);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			v[j][m] = sr[i++];
		v[j][m] = 0;
	}
	v[j] = NULL;
	return (v);
}

/**
 * _mem_set - replace memset
 * @s: var
 * @b: var
 * @n: var
 * Return: s
 */
char *_mem_set(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}

/**
 * free_mem - free dynamic memory allocated
 * @p: var
 */
void free_mem(char **p)
{
	char **i = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(i);
}

/**
 * _realoc - replace realloc
 * @ptr: var
 * @o: var
 * @n: var
 * Return: p
 */
void *_realoc(void *ptr, unsigned int o, unsigned int n)
{
	char *p;

	if (!ptr)
		return (malloc(n));
	if (!n)
		return (free(ptr), NULL);
	if (n == o)
		return (ptr);
	p = malloc(n);
	if (!p)
		return (NULL);
	o = o < n ? o : n;
	while (o--)
		p[o] = ((char *)ptr)[o];
	free(ptr);
	return (p);
}
