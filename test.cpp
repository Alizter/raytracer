#include "vector.h"
#include <stdlib.h>

//Test bed for testing ray tracer parts 

float randf() 
{ 
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX); 
}

int main()
{
	vector3	a = vector3(randf(), randf(), randf()), b = vector3(randf(), randf(), randf());
	
	std::cout << a << " X " << b << " = " << (a ^ b) << std::endl;
}


