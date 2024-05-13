#ifndef _DATA_STRUCTS_H_
#define _DATA_STRUCTS_H_

#include "Header.h"

typedef enum _node_t {
	_node_value,
	_node_op
} _node_t;

typedef enum _op_t {
	_op_add,
	_op_sub,
	_op_mul,
	_op_div,
	_op_pow,
	_op_root,
} _op_t;

typedef struct AST {
	_node_t _type;
	union {
		int _value;
		
	} 
} AST;

#endif 