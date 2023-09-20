#include "monty.h"

/**
 * stackk - changes to stack mode
 * @stack: Pointer to the top of the stack
 * @line_number: Line number being executed
 */
void stackk(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	global->mode = STACK;
}
/**
 * queue - changes to queue mode
 * @stack: Pointer to the top of the stack
 * @line_number: Line number being executed
 */
void queue(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	global->mode = QUEUE;
}
