#include "myclass.h"

#include <stdio.h>



__global__ void myclass_print()
{
	printf("hello myclass");
}

void MyClass::call_global()
{
	myclass_print << <1, 1 >> > ();
}