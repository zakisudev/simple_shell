#include "shell.h"

/**
 * free_list_t - frees a list_t
 *@head: pointer to our linked list
 */
void free_list_t(list_path *head)
{
	list_path *storage;

	while (head)
	{
		storage = head->p;
		free(head->dir);
		free(head);
		head = storage;
	}
}
