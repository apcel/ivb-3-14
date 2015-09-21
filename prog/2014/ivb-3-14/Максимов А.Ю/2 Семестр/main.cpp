#include <iostream>
#include <string>
#include "matrix.h"
#include <ctime>
#include <cstring>


int
main(int argc, char **argv)
{
	setlocale(0, "Russian");
	Matrix<int> m(10, 10, 0);

    for (int i = 1; i < 11; ++i)
        for (int j = 1; j < 11; ++j)
            m.put(i - 1, j - 1, (i + 20)*j);

    m.put(5, 5, RAND_MAX);

	std::cout << m << std::endl;
	//system("pause");
	return EXIT_SUCCESS;
}
