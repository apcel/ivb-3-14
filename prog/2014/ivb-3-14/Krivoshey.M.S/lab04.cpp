#include <fstream>

/*
	* Лаба №4
	* ИВБ-3-14
	* Кривошея Михаил
	* 12 вариант
		Определить количество дорог.
*/

int main(int argc, char **argv)
{
	std::ifstream In = std::ifstream("input.txt");
	int N, n;
	In>>N;

	int count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			In>>n;
			if(n == 1)
				count++;
		}

	In.close();
	
	count/=2;

	std::ofstream Out = std::ofstream("output.txt");
	Out<<count;
	Out.close();

	return 0;
}
