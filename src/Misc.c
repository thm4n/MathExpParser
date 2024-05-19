#include "Misc.h"

void initLogger(int argc, char** argv) {
	char* buffer = NULL;
	int bufflen = 0;
	int index = 0;
	
	buffer = (char*)malloc(sizeof(char) * (LOG_FILE_NAME_SIZE + 1));
	if(!buffer)
		exitWithError(_errcode_log_error, ERRCODE_MEM_MSG);
	snprintf(buffer, LOG_FILE_NAME_SIZE, "./logs/log_%s.log", __TIMESTAMP__);
	initDebugLog(buffer);
	free(buffer);

	for(int i = 0; i < argc; i++)
		bufflen += strlen(argv[i]) + 1;
	
	buffer = (char*)malloc(sizeof(char) * bufflen);
	if(!buffer)
		exitWithError(_errcode_log_error, ERRCODE_MEM_MSG);

	for(int i = 0; i < argc; i++)
		index += snprintf(buffer + index, bufflen - index, "%s ", argv[i]);

	buffer[bufflen - 1] = '\0';

	nonlog("entry command: '%s'", buffer);

	free(buffer);
}

char* addFileExt(const char* fileName, const char* ext) {
	char* ret = NULL;
	int len = 0;
	int i, j;

	if(!fileName || !ext) {
		return NULL;
	}

	len = strlen(fileName) + strlen(ext) + 1;
	ret = (char*)malloc(sizeof(char) * len);
	if(!ret) {
		exitWithError(_errcode_mem_err, ERRCODE_MEM_MSG);
	}

	for(i = 0; i < strlen(fileName); i++) {
		ret[i] = fileName[i];
	}
	for(j = 0; i < len; i++) {
		ret[i] = ext[j++];
	}
	ret[i - 1] = '\0';
	
	return ret;
}

int isWS(const char ch) {
	return (ch == 0x20 ||
			ch == 0x0A ||
			ch == 0x09 ||
			ch == 0x0D );
}

int isDigit(const char ch) {
	return (ch >= 0x30 && ch <= 0x39);
}

int isChar(const char ch) {
	return ((ch | 32) >= 'a' && (ch | 32) <= 'z');
}

int isSpec(const char ch) {
	return (ch == '(' || ch == ')' ||
			ch == '[' || ch == ']' ||
			ch == '{' || ch == '}' ||

			ch == '+' || ch == '-' || // add || sub
			ch == '*' || ch == '/' || // mul || div
			ch == '^' || ch == '_' || // pow || root
			ch == '%' );              // mod
}

_op_t isOp(const char* tok) {
	if(!tok)
		return _op_non;
	
	switch(tok[0]) {
	case '+':
		return _op_add;
	case '-':
		return _op_sub;
	case '*':
		return _op_mul;
	case '/':
		return _op_div;
	case '^':
		return _op_pow;
	case '_':
		return _op_root;
	case '%':
		return _op_mod;
	}

	return _op_non;
}

int isConst(const char* tok, int* value) {
	if(!tok || !value) 
		return -1;

	char* end;
	*value = strtol(tok, &end, 10);
	if(*end) 
		return -1;

	return 0;
}

int isValidName(const char* tok) {
	int len = 0;

	if(!tok)
		return false;

	len = strlen(tok);
	if(!len) 
		return false;

	if(isDigit(tok[0]) || isSpec(tok[0]))
		return false;

	for(int i = 1; i < len; i++) {
		if(!isChar(tok[i]) && !isDigit(tok[i]))
			return false;
	}

	return true;
}

char* allocateStr(const char* str, int size) {
	char* ret = NULL;
	
	if(!str)
		return NULL;

	if(size == 1) {
		ret = (char*)malloc(sizeof(char) * 2);
		if(!ret) {
			errlog(ERRCODE_MEM_MSG);
			return NULL;
		}
		ret[0] = *str;
		ret[size] = '\0';
	}
	else {
		if(size == 0)
			size = strlen(str);
		ret = (char*)malloc(sizeof(char) * (size + 1));
		if(!ret) {
			errlog(ERRCODE_MEM_MSG);
			return NULL;
		}
		memcpy(ret, str, size);
		ret[size] = '\0';
	}
	
	return ret;
}
