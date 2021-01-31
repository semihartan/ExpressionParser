#ifndef USER_H
#define USER_H
 
#include "Operation.h"



typedef struct _UserDefine
{
	char* name; // Key
	fnpUnaryOperation unOp;
	fnpResolveFunctionOperation funcOp;
	fnpResolveVariableOperation varOp;
}UserDefine;
 
typedef struct _UserDefine* ZUserDefine;

#endif // !USER_H
