#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

#define BUFFER_SIZE 80
#define REALLOC_COEF 2

enum Bool {False, True};

struct Lines
{
	size_t offset;
	size_t length;
};

struct Table
{
	size_t capacity;
	size_t size;
	struct Lines *lines;
};

struct Table table;


void table_push_back(size_t offset, size_t length)
{
	if (table.size == table.capacity)
	{
		table.lines = realloc(table.lines, sizeof(struct Lines) * table.capacity * REALLOC_COEF);
		table.capacity *= REALLOC_COEF;
	}

	table.lines[table.size].offset = offset;
	table.lines[table.size].length = length;

	++table.size;
}


size_t convert_to_number(char *buffer, size_t num_digits)
{
	size_t number = 0;
	for (int i = 0; i < num_digits; ++i)
	{
		if (isdigit(buffer[i]) == 0)
			break;

		number *= 10;

		number += (buffer[i] - 48);
	}
	return number;
}


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please, enter the file");
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	{
		fprintf(stderr, "Cannot open file. Try again later.\n");
		exit(1);
	}

	lseek(fd, 0, SEEK_SET);


	table.capacity = 0;
	table.size = 0;

	char buffer[BUFFER_SIZE];
	int actual_read;

	size_t offset = 0;
	size_t string_len = 0;
	enum Bool is_in_line = False;

	while(1)
	{
		actual_read = read(fd, buffer, BUFFER_SIZE);

		for (int i = 0; i < actual_read; ++i)
		{
			if (buffer[i] == '\n')
			{
				is_in_line = False;
				++string_len;
				table_push_back(offset, string_len);
				offset += string_len;
				string_len = 0;
			}
			else if (isspace(buffer[i]) && is_in_line == False)
			{
				++offset;
			}
			else
			{
				is_in_line = True;
				++string_len;
			}
		}

		if (actual_read < BUFFER_SIZE) //file was read
			break;
	}


	for (int i = 0; i < table.size; ++i)
	{
		printf("%u %u\n", table.lines[i].offset, table.lines[i].length);
	}


	while(1)
	{
		actual_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		size_t num_line = convert_to_number(buffer, actual_read);

		if (num_line == 0)
			break;

		if (table.size < num_line)
		{
			printf("please, enter real number string in file");
			continue;
		}

		--num_line;

		size_t line_length = table.lines[num_line].length;
		char *line = calloc(line_length + 1, sizeof(char));

		lseek(fd, table.lines[num_line].offset, SEEK_SET);
		read(fd, line, table.lines[num_line].length);
		printf("%s", line);

		free(line);
	}

	return 0;
}
