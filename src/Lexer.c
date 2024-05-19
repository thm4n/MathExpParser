#include "Lexer.h"

#define MAX_TOK_SIZE 32

int lexer(char* inputFilePath, vector* tokens) {
	char token[MAX_TOK_SIZE] = {0};
	Token* tok = NULL;
	FILE* inFile = NULL;
	int index = 0;
	char ch = 0;

	inFile = fopen(inputFilePath, "r");
	if(!inFile) {
		errlog(ERRCODE_IO_MSG);
		return _errcode_IO;
	}

	while(fread(&ch, 1, 1, inFile) == 1) {
		if(index >= MAX_TOK_SIZE) {
			dbglog("buffer exceeded with '%s'", token);
			return -1;
		}

		if(isWS(ch)) {
			dbglog("got ch: '%c'", ch);
			if(index) {
				dbglog("allocating str: token holds: '%s'", token);
				tok = createToken(token);
				if(!tok)
					dbglog("null token: '%s'", token);
				else 
					vector_append(tokens, tok);
				index = 0;
			}
			else {
				dbglog("tried to append to tokens vector empty token");
			}
		}
		else if(isChar(ch) || isDigit(ch)) {
			dbglog("got ch: '%c'", ch);
			token[index++] = ch;
		}
		else if(isSpec(ch)) {
			dbglog("got ch: '%c'", ch);
			if(index) {
				dbglog("allocating str: token holds: '%s'", token);
				tok = createToken(token);
				if(!tok)
					dbglog("null token: '%s'", token);
				else 
					vector_append(tokens, tok);
				index = 0;
			}
			token[index++] = ch;
			tok = createToken(token);
			if(!tok)
				dbglog("null token: '%s'", token);
			else 
				vector_append(tokens, tok);
			index = 0;
		}
		ch = '\0';
	}

	if(index) {
		tok = createToken(token);
		if(!tok)
			dbglog("null token: '%s'", token);
		else 
			vector_append(tokens, tok);
	}

	fclose(inFile);

	return _errcode_clean;
}

Token* createToken(char* token) {
	if(!token || token[0] == '\0') {
		dbglog("recieved empty token");
		return NULL;
	}

	_tok_t type = 0;
	int value = 0;
	_op_t op = 0;
	
	op = isOp(token);
	dbglog("on '%s' got op: %d", token, op);
	if(op != _op_non) {
		type = _tok_op;
	}		
	else if((value = isConst(token, &value) != -1)) {
		dbglog("value: %d", value);
		type = _tok_const;
	}
	else {
		dbglog("unknown token type: '%s'", token);
		return NULL;
	}

	Token* tok = (Token*)malloc(sizeof(Token));
	if(!tok)
		exitWithError(_errcode_mem_err, ERRCODE_MEM_MSG);
	
	tok->_type = type;
	if(type == _tok_op)
		tok->_op = op;
	else
		tok->_value = value;

	memset(token, 0, MAX_TOK_SIZE);

	// dbglog(" >> {op: %d, type: %d, value: %d}\n", tok->_op, tok->_type, tok->_value);
	// dbglog(" >> {op: %d, type: %d, value: %d}\n", op, type, value);

	return tok;
}
