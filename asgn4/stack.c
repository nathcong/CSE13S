
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct Stack {
	uint32_t top;
	uint32_t capacity;
	uint32_t *items;
};

Stack *stack_create(uint32_t capacity) {
	Stack *s = (Stack *) malloc(sizeof(stack));
	if (s) {
		s->top = 0;
		s->capacity = capacity;
		s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
		if (!s->items) {
			free(s);
			s = NULL;
		}
	}
	return s;
}
void stack_delete(Stack **s) {
	if (*s && (*s)->items) {
		free((*s)->items);
		free(*s);
		*s = NULL;
	}
	return;
}
uint32_t stack_size(Stack *s) {
	if (s->top == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool stack_empty(Stack *s) {

}
bool stack_full(Stack *s) {

}
bool stack_push(Stack *s, uint32_t x) {

}
bool stack_pop(Stack *s, uint32_t *x) {

}
bool stack_peek(Stack *s, uint32_t *x) {

}
void stack_copy(Stack *dst, Stack *src) {

}
void stack_print(Stack *s, FILE *outfile, char *cities[]) {

}
