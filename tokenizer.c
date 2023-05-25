#include "shell.h"

/**
 * commander - starts executing
 * @c_command: try to check current token
 * @t_command: parse token
 *
 * Return: void function
 */

void commander(char **c_command, int t_command)
{
	pid_t PID;

	if (t_command == EXTERNAL_COMMAND || t_command == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			execute_command(c_command, t_command);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(c_command, t_command);
}
