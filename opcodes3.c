#include "monty.h"

/**
 * mod - mods the top two elements of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Line number being executed
 */
void mod(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n %= (*stack)->n;
	pop(stack, line_number);
}

/**
 * pchar - prints the char at the top of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Line number being executed
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int value = (*stack)->n;

	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	if (value >= 0 && value <= 127)
		printf("%c\n", value);
	else
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
}
