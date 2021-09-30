#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 2049

struct list
{
	struct list *next;
	char *string;
};

void print_strings(struct list *root)
{
	if (root == NULL)
		return;

	do
	{
		printf("%s\n", root->string);
		root = root->next;
	} while (root != NULL);
}

int main()
{
	struct list *root = NULL;

	char *string;
	string = (char*)calloc(1, MAX_STRING_LEN);
	int string_len = 0;

	while(1)
	{
		string = fgets(string, MAX_STRING_LEN, stdin);

		if (string[0] == '.')
		{
			print_strings(root);
			break;
		}

		string_len = strlen(string);
		char *new_string = (char*)malloc(string_len + 1);
		new_string = strncpy(new_string, string, string_len + 1);

		struct list *node;

		if (root != NULL)
		{
			node = root;

			while (node->next != NULL)
				node = node->next;

			node->next = (struct list*)malloc(sizeof(struct list));
			node = node->next;
		}
		else
		{
			root = (struct list*)malloc(sizeof(struct list));
			node = root;
		}

		node->next = NULL;
		node->string = new_string;
	}
	return 0;
}