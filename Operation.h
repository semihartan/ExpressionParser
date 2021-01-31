#ifndef __OPERATION_H_
#define __OPERATION_H_

typedef double (*fnpBinaryOperation)(double, double);

typedef double (*fnpUnaryOperation)(double); 

typedef double (*fnpResolveVariableOperation)(void);

typedef double (*fnpResolveFunctionOperation)(double*);
// Binary operators
double OpAdd(double a, double b)
{
	return a + b;
}

double OpSubtract(double a, double b)
{
	return a - b;
}
double OpMultiply(double a, double b)
{
	return a * b;
}

double OpDivide(double a, double b)
{
	return a / b;
}

//Negate Operation
double OpNegate(double  var)
{
	return -var;
}
#endif // !__OPERATION_H_