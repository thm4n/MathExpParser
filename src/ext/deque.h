#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Error.h"

typedef struct deque_node {
	void* _value;

	struct deque_node* _next;
	struct deque_node* _prev;
} deque_node;

typedef struct deque {
	deque_node* _head;
	int _length;
} deque;

typedef int (*deque_opfunc)(void*, void*);

deque* deque_ctor();
void deque_dtor(deque* deq);

void deque_push_back(deque* deq, void* item);
void* deque_pop_back(deque* deq);

void deque_push_front(deque* deq, void* item);
void* deque_pop_front(deque* deq);

void deque_swap(deque* deq, int i1, int i2);
deque_node* deque_find(deque* deq, deque_opfunc opfunc, void* item);

#endif