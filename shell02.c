#include "simple_shell.h"

char **commands = NULL;
char *line = NULL;
char *shell_name = NULL;
int status = 0;

/**
 * main - command line interpreter
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 *
 * Return: 0 on success
 */


int main(int argc __attribute__((unused)), char **argv)
{
	char **cmd = NULL;
	int i, t_command = 0;
	size_t n = 0;

	signal(SIGINT, ctrl_c_handler);
	shell_name = argv[0];
	while (1)
	{
		is_nointeractive();
		_stdout("$ ", STDOUT_FILENO);
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);
			exit(status);
		}
			_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");

		for (i = 0; commands[i] != NULL; i++)
		{
			cmd = tokenizer(commands[i], " ");
			if (cmd[0] == NULL)
			{
				free(cmd);
				break;
			}
			t_command = get_command(cmd[0]);

			initializer(cmd, t_command);
			free(cmd);
		}
		free(commands);
	}
	free(line);

	return (status);
}
