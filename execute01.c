#include "shell.h"

/**
 * loop_ar - loops through commands and executes
 * @inf: var
 * @av: var
 * Return: t
 */
int loop_ar(inf_o *inf, char **av)
{
	ssize_t f = 0;
	int t = 0;

	while (f != -1 && t != -2)
	{
		initialize_info(inf);
		if (is_interactive(inf))
			_puts("$ ");
		_put_error_char(BUFSH);
		f = input_process(inf);
		if (f != -1)
		{
			populate_info(inf, av);
			t = _built_ins(inf);
			if (t == -1)
				n_built(inf);
		}
		else if (is_interactive(inf))
			_putchar('\n');
		info_free(inf, 0);
	}
	hist_file(inf);
	info_free(inf, 1);
	if (!is_interactive(inf) && inf->stat)
		exit(inf->stat);
	if (t == -2)
	{
		if (inf->err_n == -1)
			exit(inf->stat);
		exit(inf->err_n);
	}
	return (t);
}

/**
 * _built_ins - checks for builtins and process
 * @inf: var
 * Return: t
 */
int _built_ins(inf_o *inf)
{
	int j, t = -1;
	builtin_t builts[] = {
		{"exit", eexit},
		{"env", env_wrapper},
		{"help", handle_help},
		{"history", pnt_lnk_lst},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", handle_cd},
		{"alias", mng_alias},
		{NULL, NULL}
	};

	for (j = 0; builts[j].type; j++)
	{
		if (_compare_str(inf->argv[0], builts[j].type) == 0)
		{
			inf->lcount++;
			t = builts[j].func(inf);
			break;
		}
	}
	return (t);
}

/**
 * n_built - handle non builtin commands
 * @inf: var
 */
void n_built(inf_o *inf)
{
	char *p = NULL;
	int j, k;

	inf->path = inf->argv[0];
	if (inf->lcount_f == 1)
	{
		inf->lcount++;
		inf->lcount_f = 0;
	}
	for (j = 0, k = 0; inf->arg[j]; j++)
	{
		if (!is_delim(inf->arg[j], " \t\n"))
			k++;
	}
	if (!k)
		return;

	p = cmd_executable(inf, get_env_var(inf, "PATH="), inf->argv[0]);
	if (p)
	{
		inf->path = p;
		cmd_fokr(inf);
	}
	else
	{
		if ((is_interactive(inf) || get_env_var(inf, "PATH=")
			|| inf->argv[0][0] == '/') && command_valid(inf, inf->argv[0]))
			cmd_fokr(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->stat = 127;
			error_pnt(inf, "not found\n");
		}
	}
}

/**
 * cmd_fokr - fork a process
 * @inf: var
 */
void cmd_fokr(inf_o *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_env(inf)) == -1)
		{
			info_free(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->stat));
		if (WIFEXITED(inf->stat))
		{
			inf->stat = WEXITSTATUS(inf->stat);
			if (inf->stat == 126)
				error_pnt(inf, "Permission denied\n");
		}
	}
}
