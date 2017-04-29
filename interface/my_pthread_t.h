#include <malloc.h>
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_STACK 1024*64

int my_pthread_create(ucontext_t *thread, void (*function)(), void *arg);
void my_pthread_yield();
void my_pthread_exit(void *value_ptr);
int my_pthread_join(ucontext_t thread, void **value_ptr);