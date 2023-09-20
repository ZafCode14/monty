#include "monty.h"

int value;

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
		if (opcode[0] == '#')
			continue;
		value_str = strtok(NULL, " \t\n");
		execute(opcode, value_str, line_number, &stack);
	}
	free(line);
	fclose(file);
	free_stack(&stack);
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
	int i;
	instruction_t instructions[] = {
		{"push", push}, {"pall", pall}, {"pint", pint},
		{"pop", pop}, {"swap", swap}, {"add", add},
		{"nop", nop}, {"div", divi}, {"mul", mul},
		{"mod", mod}, {"sub", sub}, {"pchar", pchar},
		{NULL, NULL}
	};

	if (opcode)
	{
		for (i = 0; instructions[i].opcode; i++)
		{
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
					value = atoi(value_str);
				}
				instructions[i].f(stack, line_number);
			}
			else if (strcmp(opcode, "pall") != 0 && strcmp(opcode, "push") != 0 &&
					strcmp(opcode, "pop") != 0 && strcmp(opcode, "swap") != 0 &&
					strcmp(opcode, "add") != 0 && strcmp(opcode, "nop") != 0 &&
					strcmp(opcode, "div") != 0 && strcmp(opcode, "mul") != 0 &&
					strcmp(opcode, "sub") != 0 && strcmp(opcode, "pchar") != 0 &&  
					strcmp(opcode, "mod") != 0 && strcmp(opcode, "pint") != 0)
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
				free_stack(stack);
				exit(EXIT_FAILURE);
			}
		}
	}
}
