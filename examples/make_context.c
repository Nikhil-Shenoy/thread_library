#include <malloc.h>
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

#define FIBER_STACK 1024*64

ucontext_t child, parent;

void thread_function() {
	printf("Child thread yielding to parent\n");
	swapcontext(&child, &parent);
	printf("Child thread exiting\n");
	swapcontext(&child, &parent);
}

int main() {
	getcontext(&child);

	child.uc_link = 0;
	child.uc_stack.ss_sp = malloc(FIBER_STACK);
	child.uc_stack.ss_size = FIBER_STACK;
	child.uc_stack.ss_flags = 0;

	if(child.uc_stack.ss_sp == 0) {
		perror("malloc: Could not allocate stack");
		exit(1);
	}

	printf("Creating child thread\n");
	makecontext(&child, &thread_function, 0);

	printf("Switching to child thread\n");
	swapcontext(&parent, &child);
	printf("Switching to child thread again\n");
	swapcontext(&parent, &child);

	free(child.uc_stack.ss_sp);

	printf("Child thread returned and stack freed\n");

	return 0;
}