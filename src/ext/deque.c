#include "deque.h"

#define DEQ_ERR_MEM_ALLOC    "deque: could not allocate memory"
#define DEQ_ERR_NULL_REC     "deque: recieved NULL"
#define DEQ_ERR_OUT_OF_BOUND "deque: index out of vector bounds"

deque* deque_ctor() {
	deque* deq = (deque*)malloc(sizeof(deque));
	if(!deq)
		exitWithError(_errcode_external, DEQ_ERR_MEM_ALLOC);

	deq->_head = NULL;
	deq->_length = 0;
	
	return deq;
}

void deque_dtor(deque* deq) {
	deque_node* curr;
	deque_node* next;
	if(deq) {
		curr = deq->_head;
		while(curr) {
			next = curr->_next;
			free(curr);
			curr = next;
		}	
	}
}

void deque_push_back(deque* deq, void* item) {
	deque_node* curr = NULL;
	deque_node* next = NULL;
	
	if(!deq)
		exitWithError(_errcode_external, DEQ_ERR_MEM_ALLOC);

	curr = deq->_head;

	while(curr && curr->_next) {
		curr = curr->_next;
	}

	next = (deque_node*)malloc(sizeof(deque_node));
	if(!next)
		exitWithError(_errcode_external, DEQ_ERR_MEM_ALLOC);

	next->_next = NULL;
	next->_value = item;

	if(deq->_head) {
		next->_prev = curr;
		curr->_next = next;
	}
	else {
		deq->_head = next;
		next->_prev = NULL;
	}
}

void* deque_pop_back(deque* deq) {
	deque_node* curr = NULL;
	deque_node* last = NULL;
	void* item = NULL;
	
	if(!deq)
		exitWithError(_errcode_external, DEQ_ERR_MEM_ALLOC);

	if(!deq->_head) 
		return NULL;

	last = deq->_head;
	while(last && last->_next) {
		last = last->_next;
	}
	
	curr = last->_prev;
	curr->_next = NULL;

	item = last->_value;
	free(last);
	return item;
}

void deque_push_front(deque* deq, void* item) {
	deque_node* newNode = NULL;
	
	if(!deq)
		exitWithError(_errcode_external, DEQ_ERR_MEM_ALLOC);

	if(!deq->_head)
		return NULL;

	newNode = (deque_node*)malloc(sizeof(deque_node));
	if(!newNode)
		exitWithError(_errcode_external, DEQ_ERR_MEM_ALLOC);

	newNode->_next = deq->_head;
	newNode->_prev = NULL;
	newNode->_value = item;
	deq->_head = newNode;
}

void* deque_pop_front(deque* deq) {
	deque_node* ret = NULL;
	void* item = NULL;
	
	if(!deq)
		exitWithError(_errcode_external, DEQ_ERR_MEM_ALLOC);

	if(!deq->_head)
		return NULL;

	ret = deq->_head;

	deq->_head = deq->_head->_next;
	deq->_head->_prev = NULL;

	item = ret->_value;
	free(ret);
	return item;
}

void deque_swap(deque* deq, int i1, int i2) {

}

deque_node* deque_find(deque* deq, deque_opfunc opfunc, void* item) {

}

