#include "shell.h"

/**
 * main - process everything
 * @ac: var
 * @av: var
 * Return: 0
 */
int main(int ac, char **av)
{
	inf_o inf[] = { INF_IN };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts_error(av[0]);
				_puts_error(": 0: Can't open ");
				_puts_error(av[1]);
				_put_error_char('\n');
				_put_error_char(BUFSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = fd;
	}
	penv_list(inf);
	read_hist_file(inf);
	loop_ar(inf, av);
	return (EXIT_SUCCESS);
}

/**
 * input_process - get input and process it
 * @inf: struct
 * Return: s
 */
ssize_t input_process(inf_o *inf)
{
         static char *b;
         static size_t i, j, l;
         ssize_t s = 0;
         char **bs = &(inf->arg), *p;

         _putchar(BUFSH);
         s = buf_save(inf, &b, &l);
        if (l)
        {
                j = i;
                p = b + i;
                mod_chain(inf, b, &j, i, l);
                while (j < l)
                {
                        i = l = 0;
                        inf->cmdb_type = NORM;
                }
                 *bs = p;
                return (_length_str(p));
        }
        *bs = b;
        return (s);
}
