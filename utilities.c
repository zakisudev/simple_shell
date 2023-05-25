#include "simple_shell.h"

/** get_cmd - determines the type of the command
 * @cmd: command to be parsed
 *
 * Return: constant representing the type of the command
 */

int get_cmd(char *cmd)
{
	int i;
	char *in_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; in_command[i] != NULL; i++)
	{
		if (_strcmp(cmd, in_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - checks if a command is found in the PATH */
	path = check_path(cmd);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execcmd - executes a command
 * @tok_command: tokenized form of the command
 * @command_type: type of the command
 *
 * Return: void
 */
void execcmd(char **tok_command, int command_type)
{
	void (*func)(char **command);

	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tok_command[0], tok_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMAND)
	{
		if (execve(check_path(tok_command[0]), tok_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == INTERNAL_COMMAND)
	{
		func = get_func(tok_command[0]);
		func(tok_command);
	}
	if (command_type == INVALID_COMMAND)
	{
		_stdout(shell_name, STDERR_FILENO);
		_stdout(": 1: ", STDERR_FILENO);
		_stdout(tok_command[0], STDERR_FILENO);
		_stdout(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * check_path - checks if a command is found in the PATH
 * @cmd: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(char *cmd)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || __strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (__strlen(path) + 1));
	__strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, cmd);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * parse_func - retrieves a function based on the command given and a mapping
 * @cmd: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*parse_func(char *cmd))(char **)
{
	int i;
	function_map mapping[] = {
		{"env", env}, {"exit", exit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(cmd, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_cpy = name;
		     *pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}

