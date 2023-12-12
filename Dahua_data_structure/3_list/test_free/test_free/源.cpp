#include <iostream>
#include <corecrt_malloc.h>


int main()
{
	//int* p = new int;
	int* p = (int*)malloc(sizeof(int)*1000000);
	*p = 4;
	std::cout << *p<< std::endl;
	delete p;
	//free(p);
	//free(p);
	return 0;
}
