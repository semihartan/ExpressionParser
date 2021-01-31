#ifndef VECTOR_H
#define VECTOR_H

#include <malloc.h>


#define VECTOR_INIT(vec) Vector vec;


typedef struct _Vector
{
	void** items;
	int total;
	int capacity;

}Vector;
 
typedef struct _Vector* ZVector;


void VectorInit(ZVector* vec)
{
	*vec = (ZVector)malloc(sizeof(Vector));
	(*vec)->items = (void**)malloc(sizeof(void*) * 6);
	(*vec)->capacity = 6;
	(*vec)->total = 0;
}
void VectorResize(ZVector v, int capacity)
{  
	void** items = (void**)realloc(v->items, sizeof(void*) * capacity);
	if (items)
	{
		v->items = items;
		v->capacity = capacity; 
	} 
}
void VectorPushBack(ZVector vec, void* item)
{
	if (vec->total == vec->capacity) 
		VectorResize(vec, vec->capacity * 2); 

	vec->items[vec->total++] = item;
}
void VectorSet(ZVector vec, int index, void* item)
{  
	if ((index >= 0) && (index < vec->total))
	{
		vec->items[index] = item; 
	} 
}
void* VectorGet(ZVector vec, int index)
{
	void* readData = NULL; 
	if ((index >= 0) && (index < vec->total))
	{
		readData = vec->items[index];
	} 
	return readData;
} 
void VectorDelete(ZVector vec, int index)
{ 
	int i = 0; 
		if ((index < 0) || (index >= vec->total))
			return;
		vec->items[index] = NULL;
		for (i = index; (i < vec->total - 1); ++i)
		{
			vec->items[i] = vec->items[i + 1];
			vec->items[i + 1] = NULL;
		}
		vec->total--;
		if ((vec->total > 0) && ((vec->total) == (vec->capacity / 4)))
		{
			VectorResize(vec, vec->capacity / 2);
		} 
}
#endif // !VECTOR_H
