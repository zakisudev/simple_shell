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
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
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

	for (; tokenized_command[token] != NULL; token++)
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
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(cmd[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
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
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
