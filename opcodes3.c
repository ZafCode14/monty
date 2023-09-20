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
	int value;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	value = (*stack)->n;
	if (value < 0 || value > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", value);
}

/**
 * pstr - prints the string starting at the top of the stack
 * @stack: Pointer to the top of the stack
 * @line_number: Line number being executed
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	int value;
	unsigned int i;
	stack_t *temp = *stack;

	if (line_number > 1)
	{
		for (i = 0; i < line_number; i++)
		{
			value = temp->n;
			if (value < 0 || value > 127 || value == 0)
				break;
			printf("%c", value);
			temp = temp->next;
		}
	}
	printf("\n");
}

/**
 * rotl - Rotates the stack to the left
 * @stack: Pointer to the top of the stack
 * @line_number: Line number being executed
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *last;
	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	temp = *stack;
	last = *stack;

	while (last->next != NULL)
		last = last->next;

	*stack = temp->next;
	(*stack)->prev = NULL;

	last->next = temp;
	temp->prev = last;
	temp->next = NULL;
}
