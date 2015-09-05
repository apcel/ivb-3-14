#include <iostream>

template <typename Type>
class allocator {
public:
	Type * allocate(int size){

		return new Type(size);
	}
	void deallocate(Type * mem){
		delete mem;
	}
};




void
main()
{
	allocator<int> size;
	int *a = size.allocate(2); 
	size.deallocate(a);
	system("pause");
}