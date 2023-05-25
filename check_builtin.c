#include "simple_shell.h"

/**
 * p_env - prints the current_environnement
 * @cmd: command entered
 *
 * Return: void
 */

void penv(char **cmd __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_stdout(environ[i], STDOUT_FILENO);
		_stdout("\n", STDOUT_FILENO);
	}
}

/**
 * eexit - exits the shell
 * @cmd: command entered
 *
 * Return: void
 */

void eexit(char **cmd)
{
	int token = 0, arg;

	for (; cmd[token] != NULL; token++)
		;
	if (token == 1)
	{
		free(cmd);
		free(line);
		free(commands);
		exit(status);
	}
	else if (token == 2)
	{
		arg = _atoi(cmd[1]);
		if (arg == -1)
		{
			_stdout(shell_name, STDERR_FILENO);
			_stdout(": 1: exit: Illegal number: ", STDERR_FILENO);
			_stdout(cmd[1], STDERR_FILENO);
			_stdout("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(cmd);
			free(commands);
			exit(arg);
		}
	}
	else
		_stdout("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
