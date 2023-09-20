#include "monty.h"

/**
 * free_stack - Frees a stack
 * @stack: Pointer to the stack
 */
void free_stack(stack_t **stack)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL)
		return;

	while (*stack)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
}
/**
 * is_integer - Checks if a string is a number
 * @str: String to check
 * Return: 1 if true, 0 if false
 */
int is_integer(char *str)
{
	int i = 0;

	if (str[0] == '-')
		i = 1;

	for (; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}
