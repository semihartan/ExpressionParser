#ifndef __PARSER_H_
#define __PARSER_H_

#include "Vector.h"
#include "Tokenizer.h"
#include "Node.h"
#include "Operation.h"
#include "User.h"
#include "String.h"

#define TOKENIZER  parser->tokenizer

ZNode ParseUnary(ZParser);

typedef struct _Parser
{
	ZTokenizer tokenizer;
	ZVector userDefinitions;
}Parser;

typedef struct _Parser* ZParser;

void AddFunc(ZParser parser, char* name, fnpResolveFunctionOperation op)
{
	ZUserDefine func  = (ZUserDefine)malloc(sizeof(UserDefine));
	func->name = CopyStringToHeap(name);
	func->funcOp = op;
	VectorPushBack(parser->userDefinitions, func);
}
void AddVar(ZParser parser, char* name, fnpResolveVariableOperation op)
{
	UserDefine var;
	var.name = CopyStringToHeap(name);
	var.varOp = op;
	VectorPushBack(parser->userDefinitions, &var);
}
ZUserDefine GetUserDefine(ZParser parser, char* name)
{
	ZUserDefine ret = NULL;
	ZVector userDefines = parser->userDefinitions;
	for (int i = 0; i < userDefines->total; i++)
	{
		ret = (ZUserDefine)userDefines->items[i];
		if (CompareStrings(ret->name, name))
			return ret;
	}
	return ret;
}

ZParser CreateParser(const char* expression)
{
	ZTokenizer tokenizer = (ZTokenizer)malloc(sizeof(Tokenizer));	
	memset(tokenizer, 0, sizeof(Tokenizer));
	InitializeTokenizer(tokenizer, expression);
	ZParser parser = (ZParser)malloc(sizeof(Parser));
	parser->tokenizer = tokenizer;
	VectorInit(&(parser->userDefinitions));
	return parser;
}
ZNode ParseMultiplyDivide(ZParser parser)
{
	ZNode lhs = ParseUnary(parser);
	while (1)
	{
		fnpBinaryOperation op = NULL;
		if (TOKENIZER->token == TMultiply)
		{
			op = OpMultiply;
		}
		else if (TOKENIZER->token == TDivide)
		{
			op = OpDivide;
		}
		if (op == NULL)
			return lhs;

		NextToken(TOKENIZER);
		ZNode rhs = ParseUnary(parser);
		lhs = CreateNodeBinary(lhs, rhs, op);
	}
}
ZNode ParseAddSubtract(ZParser parser)
{
	ZNode lhs = ParseMultiplyDivide(parser);

	while (1)
	{
		fnpBinaryOperation op = NULL;
		if (TOKENIZER->token == TAdd)
		{
			op = OpAdd;
		}
		else if (TOKENIZER->token == TSubtract)
		{
			op = OpSubtract;
		}
		if (!op)
			return lhs;
		NextToken(TOKENIZER);
		ZNode rhs = ParseMultiplyDivide(parser);
		lhs = CreateNodeBinary(lhs, rhs, op);
	}
}
ZNode ParseLeaf(ZParser parser)
{
	if (TOKEN(TOKENIZER) == TNumber)
	{
		ZNode node = CreateNodeNumber(TOKENIZER->number);
		NextToken(TOKENIZER);
		return node;
	}

	if (TOKEN(TOKENIZER) == TOpenParens)
	{
		NextToken(TOKENIZER); // Skip open parens
		ZNode node = ParseAddSubtract(parser);
		NextToken(TOKENIZER); // Skip closed parens too!
		return node;
	}

	if (TOKEN(TOKENIZER) == TIdentifier)
	{
		char* name = TOKENIZER->identifier;
		NextToken(TOKENIZER); // Get the name and skip it
		ZUserDefine userDefine = GetUserDefine(parser, name);

		if (TOKEN(TOKENIZER) != TOpenParens)
		{
			return CreateNodeVariable(userDefine->varOp);
		}
		else
		{
			// Function call

            // Skip open parens
			NextToken(TOKENIZER);
			ZVector arguments = NULL;
			VectorInit(&arguments);
			while (1)
			{
				VectorPushBack(arguments, ParseAddSubtract(parser));
				if (TOKEN(TOKENIZER) == TComma)
				{
					NextToken(TOKENIZER); 
					continue;
				}
				break;
			}

			NextToken(TOKENIZER);//Skip close parens

			return CreateNodeFunctionCall(userDefine->funcOp, arguments);
		}
	}
}
ZNode ParseUnary(ZParser parser)
{
	if (TOKEN(TOKENIZER) == TAdd)
	{
		NextToken(TOKENIZER);
		return ParseUnary(parser);
	}
	if (TOKEN(TOKENIZER) == TSubtract)
	{
		NextToken(TOKENIZER);
		ZNode rhs = ParseUnary(parser);

		return CreateNodeUnary(OpNegate);
	}

	// No positive/negative operator so parse a leaf node
	return ParseLeaf(parser);
}

ZNode ParseExpression(ZParser parser)
{
	ZNode expr = ParseAddSubtract(parser);
	return expr;
}
#endif