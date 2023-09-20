#include "monty.h"

global_t *global;

/**
 * main - the main function
 * @argc: argument count
 * @argv: argument value
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *opcode, *value_str;
	int line_number = 0;
	stack_t *stack = NULL;

	global = malloc(sizeof(global_t));
	if (global == NULL)
	{
		fprintf(stderr, "Error: Failed to allocate memory for global\n");
		exit(EXIT_FAILURE);
	}
	global->mode = STACK;
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		value_str = strtok(NULL, " \t\n");
		execute(opcode, value_str, line_number, &stack);
	}
	free(line);
	fclose(file);
	free_stack(&stack);
	free(global);
	exit(EXIT_SUCCESS);
}

/**
 * execute - executes the opcodes
 * @opcode: pointer to the opcode string
 * @value_str: pointer to the string value
 * @line_number: the line number
 * @stack: pointer to pointer to head node
 */
void execute(char *opcode, char *value_str, int line_number, stack_t **stack)
{
	int i, found = 0;
	instruction_t instructions[] = {
		{"push", push}, {"pall", pall}, {"pint", pint}, {"pop", pop},
		{"swap", swap}, {"add", add}, {"nop", nop}, {"div", divi},
		{"mul", mul}, {"mod", mod}, {"sub", sub}, {"pchar", pchar},
		{"pstr", pstr}, {"rotl", rotl}, {"rotr", rotr},
		{"stack", stackk}, {"queue", queue}, {NULL, NULL}
	};

	if (opcode)
	{
		for (i = 0; instructions[i].opcode; i++)
			if (strcmp(opcode, instructions[i].opcode) == 0)
				found = 1;
		for (i = 0; instructions[i].opcode; i++)
		{
			if (opcode[0] == '#')
				continue;
			if (strcmp(instructions[i].opcode, opcode) == 0)
			{
				if (strcmp(opcode, "push") == 0)
				{
					if (value_str == NULL || !is_integer(value_str))
					{
						fprintf(stderr, "L%d: usage: push integer\n", line_number);
						free_stack(stack);
						exit(EXIT_FAILURE);
					}
					global->value = atoi(value_str);
				}
				instructions[i].f(stack, line_number);
			}
			else if (!found)
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
				free_stack(stack);
				exit(EXIT_FAILURE);
			}
		}
	}
}
