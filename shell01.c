#include "simple_shell.h"

/**
 * is_noninteractive - handles non_interactive mode
 *
 * Return: void
 */

void is_noninteractive(void)
{
	char **c_command = NULL;
	int i, t_command = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &n, stdin) != -1)
		{
			_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");
			for (i = 0; commands[i] != NULL; i++)
			{
				c_command = tokenizer(commands[i], " ");
				if (c_command[0] == NULL)
				{
					free(c_command);
					break;
				}
				t_command = get_cmd(c_command[0]);
				commander(c_command, t_command);
				free(c_command);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
