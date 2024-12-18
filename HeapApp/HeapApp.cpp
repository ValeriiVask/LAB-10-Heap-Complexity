#include <iostream>
#include <vector>
#include "../HeapLib/Heap.h"

int main()
{
	size_t size;
	do
	{
		std::cout << "Enter size:";
		std::cin >> size;
		if (size > 0)
		{
			Heap<int, int> heap;
			for (int i = 1; i <= size; ++i)
				heap.insert({ i, i });
			std::cout << heap;
		}
	} while (size > 0);
}
