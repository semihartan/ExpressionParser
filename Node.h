#ifndef __NODE_H_
#define __NODE_H_

#include <malloc.h>
#include "Operation.h"
#include "Vector.h"

typedef enum _NodeType
{
	Number,
	Binary,
	Unary,
	CallFunc,
	CallVar,
}NodeType;

typedef struct _Node* ZNode;

typedef struct _Node
{
	NodeType type;
	ZNode lhs;
	ZNode rhs;
	double number;

	fnpBinaryOperation binOperation;
	
	fnpUnaryOperation unOperation;

	ZVector args;
	fnpResolveFunctionOperation funcOperation;
	 
	fnpResolveVariableOperation varOperation;
}Node;

double Evaluate(ZNode node)
{
	switch (node->type)
	{
		case Number:
			return node->number;
		case Unary:
			return node->unOperation(node->number);
		case Binary:
		{
			double lhsValue = Evaluate(node->lhs);
			double rhsValue = Evaluate(node->rhs);
			return node->binOperation(lhsValue, rhsValue);
		}
		case CallVar: 
			return node->varOperation(); 
		case CallFunc:
		{
			int count = node->args->total;
			double* args = (double*)malloc(count);
			for (int i = 0; i < count; i++)
			{
				ZNode argNode = (ZNode)VectorGet(node->args, i);
				args[i] = Evaluate(argNode);
			}
			return node->funcOperation(args);
		}
	}
}
ZNode CreateNodeBinary(ZNode lhs, ZNode rhs, fnpBinaryOperation op)
{
	ZNode node = (ZNode)malloc(sizeof(Node));
	node->type = Binary;
	node->lhs = lhs;
	node->rhs = rhs;
	node->number = 0.0f;
	node->binOperation = op;
	node->unOperation = NULL;
	return node;
}
ZNode CreateNodeNumber(double number)
{
	ZNode node = (ZNode)malloc(sizeof(Node));
	node->type = Number;
	node->lhs = NULL;
	node->rhs = NULL;
	node->binOperation = NULL;
	node->unOperation = NULL;
	node->number = number;
	return node;
}
ZNode CreateNodeUnary(fnpUnaryOperation op)
{
	ZNode node = (ZNode)malloc(sizeof(Node));
	node->type = Unary;
	node->lhs = NULL;
	node->rhs = NULL;
	node->binOperation = NULL;
	node->unOperation = op;
	node->number = 0.0;
	return node;
}
ZNode CreateNodeVariable(fnpResolveVariableOperation op)
{
	ZNode node = (ZNode)malloc(sizeof(Node));
	node->type = CallVar;
	node->lhs = NULL;
	node->rhs = NULL;
	node->binOperation = NULL;
	node->args = NULL;
	node->funcOperation = NULL; 
	node->varOperation = op;
	node->unOperation = NULL;
	node->number = 0.0;
	return node;
}
ZNode CreateNodeFunctionCall(fnpResolveFunctionOperation op, ZVector argNodes)
{
	ZNode node = (ZNode)malloc(sizeof(Node));
	node->type = CallFunc;
	node->lhs = NULL;
	node->rhs = NULL;
	node->binOperation = NULL;
	node->unOperation = NULL;
	node->funcOperation = op;
	node->varOperation = NULL;
	node->number = 0.0; 
	node->args = argNodes;
	return node;
}
#endif // !_NODE_H_
