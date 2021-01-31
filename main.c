#include <stdio.h>
#include <conio.h>

#include "expengine.h"


double myfunc(double* args)
{
	return 5 * (*args);
}

int main()
{ 
	//"50 + 4 * 2 / 4 - 9 + 3 * 6 - 2 * 4 - 5 * 6 - 0"
	char* expr = "50 + 4 * 2/ 4 - 9 + 3 * 6 * myfunc(5+6)";
	ZParser parser = CreateParser(expr); // Create a parser to read the expression
	AddFunc(parser, "myfunc", myfunc); // Add custom function definition 
	ZNode root = ParseExpression(parser);  // Get the root node of the expression tree. 
	double result = Evaluate(root); // Finally, evaluate the tree starting from root.
	printf("Result = %lf\n", result); // Print the result
	getchar();
	return 0;
}