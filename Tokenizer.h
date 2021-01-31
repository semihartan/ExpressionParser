#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdlib.h>
#include <memory.h>
#include <ctype.h>


#define EXPRESSION(tokenizer) tokenizer##->expression
#define TOKEN(tokenizer) tokenizer##->token
#define CURCHAR(tokenizer) tokenizer##->currentChar

typedef enum _TokenType
{
	EOT,
	TNumber,
	TSubtract,
	TAdd,
	TMultiply,
	TDivide,
	TOpenParens,
	TCloseParens,
	TIdentifier,
	TComma
}TokenType;



typedef struct _Tokenizer
{
	const char* expression;
	char currentChar;
	TokenType token;
	char* identifier;
	double number;
	int charPosition;
}Tokenizer, *ZTokenizer;

// Set the current char to the next char in the expression
void NextChar(ZTokenizer tokenizer)
{
	if (tokenizer->expression)
	{
		char ch = EXPRESSION(tokenizer)[tokenizer->charPosition++];
		if (ch != '\0')
			CURCHAR(tokenizer) = ch;
		else
			CURCHAR(tokenizer) = '\0';
	}
}
void NextToken(ZTokenizer tokenizer)
{
	// We skip white spaces.
	while (isspace(CURCHAR(tokenizer)))
	{
		NextChar(tokenizer);
	}
	// This section is self-explanatory
	switch (CURCHAR(tokenizer))
	{
		case '\0':
			TOKEN(tokenizer) = EOT;
			NextChar(tokenizer);
			return;
		case '+':
			TOKEN(tokenizer) = TAdd;
			NextChar(tokenizer);
			return;
		case '-':
			TOKEN(tokenizer) = TSubtract;
			NextChar(tokenizer);
			return;
		case '*':
			TOKEN(tokenizer) = TMultiply;
			NextChar(tokenizer);
			return;
		case '/':
			TOKEN(tokenizer) = TDivide;
			NextChar(tokenizer);
			return;
		case '(':
			TOKEN(tokenizer) = TOpenParens;
			NextChar(tokenizer);
			return;
		case ')':
			TOKEN(tokenizer) = TCloseParens;
			NextChar(tokenizer);
			return;
		case ',':
			TOKEN(tokenizer) = TComma;
			NextChar(tokenizer);
			return;
		default:
			break;
	}
	// Tokenize real numbers
	if (isdigit(CURCHAR(tokenizer)) || CURCHAR(tokenizer) == '.')
	{
		int haveDecimalPoint = 0; // A Boolean value indicating whether we reach  a decimal point
		char buffer[64]; // A temporary buffer for storing the number
		int i = 0;
		// Self-explanatory
		while (isdigit(CURCHAR(tokenizer)) || (!haveDecimalPoint && CURCHAR(tokenizer) == '.'))
		{
			buffer[i++] = CURCHAR(tokenizer);
			haveDecimalPoint = CURCHAR(tokenizer) == '.';
			NextChar(tokenizer);
		}
		buffer[i] = '\0'; // Add null terminating character
		tokenizer->number = strtod(buffer, NULL); // Parse the string containing real number, this standard func returns a double-precision floating-point number.
		TOKEN(tokenizer) = TNumber; // Set the token type
		return;
	}
	// Identifier - starts with letter or underscore
	if (isalpha(CURCHAR(tokenizer)) || CURCHAR(tokenizer) == '_')
	{
		char* buffer = malloc(64);  // Allocate some heap memory for identifier name because we need a permanent storage
		int i = 0;
		while (isalpha(CURCHAR(tokenizer)) || CURCHAR(tokenizer) == '_') // If the current char is a alpha char or a underscore
		{
			buffer[i++] = CURCHAR(tokenizer);
			NextChar(tokenizer);
		}
		buffer[i] = '\0';
		tokenizer->identifier = buffer;
		TOKEN(tokenizer) = TIdentifier;
		return;
	}
}


void InitializeTokenizer(ZTokenizer tokenizer, const char* expr)
{
	tokenizer->expression = expr;
	NextChar(tokenizer);
	NextToken(tokenizer);
}


#endif // !TOKENIZER_H
