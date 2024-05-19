#ifndef _DATA_STRUCTS_H_
#define _DATA_STRUCTS_H_

#include "Header.h"

typedef enum _node_t {
	_node_value,
	_node_op
} _node_t;

typedef enum _op_t {
	_op_non  = 0,
	_op_add  = 1,
	_op_sub  = 2,
	_op_mul  = 3,
	_op_div  = 4,
	_op_pow  = 5,
	_op_root = 6,
	_op_mod  = 7,
} _op_t;

typedef enum _tok_t {
	_tok_const = 1,
	_tok_op    = 2,
} _tok_t;

typedef struct Token {
	_tok_t _type;
	union {
		int _value;
		_op_t _op;
	};
} Token;

typedef struct AST {
	_node_t _type;
	Token* _value;
	struct AST* _lhs;
	struct AST* _rhs;
} AST;

#endif 