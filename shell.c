#include "shell.h"

/**
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */
void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_puts("\n$ ");
	}
}

/**
* _EOF - handles the End of File
* @len: return value of getline function
* @buff: buffer
 */
void _EOF(int len, char *buff)
{
	(void)buff;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}
/**
  * _isatty - verif if terminal
  */

void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
}
/**
 * main - Shell
 * Return: 0 on success
 */

int main(void)
{
	ssize_t len = 0;
	char *buff = NULL, *value, *pathname, **arv;
	size_t size = 0;
	list_path *head = NULL;
	void (*f)(char **);

	signal(SIGINT, sig_handler);
	while (len != EOF)
	{
		_isatty();
		len = getline(&buff, &size, stdin);
		_EOF(len, buff);
		arv = tokenizer(buff, " \n");
		if (!arv || !arv[0])
			exec(arv);
		else
		{
			value = _get_env("PATH");
			head = link_path(value);
			pathname = _where(arv[0], head);
			f = _builtin_check(arv);
			if (f)
			{
				free(buff);
				f(arv);
			}
			else if (!pathname)
				exec(arv);
			else if (pathname)
			{
				free(arv[0]);
				arv[0] = pathname;
				exec(arv);
			}
		}
	}
	free_list_t(head);
	free_arv(arv);
	free(buff);
	return (0);
}
