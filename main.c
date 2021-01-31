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
	ZParser parser = CreateParser(expr);
	AddFunc(parser, "myfunc", myfunc);
	ZNode root = ParseExpression(parser); 
	double result = Evaluate(root);
	printf("Result = %lf\n", result);
	getchar();
	return 0;
}