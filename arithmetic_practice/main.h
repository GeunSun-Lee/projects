#if !defined(__MAIN_H__)
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

#define ESC 27
#define RESULT_TRUE 0
#define RESULT_FALSE -1

typedef enum OP_TYPE {
	OP_TYPE_PLUS = 0,
	OP_TYPE_MINUS,
	OP_TYPE_MULTIPLE,
	OP_TYPE_MAX,
} OP_TYPE;

int print_result(int result);
int check_result(int op, int x, int y, int val);

#endif //__MAIN_H__
