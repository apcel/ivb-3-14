#include <fstream>

int main(int argc, char **argv)
{
	std::ifstream In("input.txt");

	if(!In.is_open())
		return -1;

	std::ofstream Out("output.txt");
	
	int k,n,m,d;
	In>>k;
	for (int i = 0; i < k; i++)
	{
		In>>n;
		In>>m;

		d = 19*m + ((n+239)*(n+366))/2;
		Out<<d;

		if(i+1<k)
			Out<<'\n';
	}

	In.close();
	Out.close();
	return EXIT_SUCCESS;
}
