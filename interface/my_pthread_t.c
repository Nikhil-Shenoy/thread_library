#include "my_pthread_t.h"

ucontext_t parent;

int my_pthread_create(ucontext_t *thread, void (*function)(), void *arg){
	// typedef pthread_t to a ucontext_t

	printf("getcontext()\n");
	getcontext(thread);

	// If non-zero, specifies the next context to run after this one finishes.
	thread->uc_link = 0; 
	// Allocate memory for the stack
	thread->uc_stack.ss_sp = malloc(THREAD_STACK);
	// Store the size of the stack
	thread->uc_stack.ss_size = THREAD_STACK;

	if(thread->uc_stack.ss_sp == 0) {
		perror("malloc: Could not allocate stack\n");
		return -1;
	}

	// Make the new thread
	printf("makecontext\n");
	makecontext(thread,function,0);

	// Let's just try something simple for now

	printf("swapcontext\n");
	swapcontext(&parent,thread);
	printf("Returned from child thread.\n");

	free(thread->uc_stack.ss_sp);

	printf("Done!\n");

	return 0;

}

// void my_pthread_yield() {

// }

void my_pthread_exit(void *value_ptr) {
	// Should this be setcontext or swapcontext?
	setcontext(&parent);
}


// int my_pthread_join(pthread_t thread, void **value_ptr) {
// 	return 0;
// }