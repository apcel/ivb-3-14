// 17 вариант
#include <fstream>
#include <string>

using std::ifstream;
using std::ofstream;

struct Sphere{
	int X,Y,R;
};

Sphere ReadSphere(ifstream &stream);
void PrintSphere(Sphere s, int numder);
bool IsSphereContect(Sphere s1, Sphere s2);

int main(int argc, char **argv)
{
	setlocale(0, "Russian");
	ifstream In = ifstream("input.txt");

	if(!In.is_open())
	{
		printf_s("Нет файла :(\n");
		return -1;
	}
	
	Sphere s1 = ReadSphere(In);
	Sphere s2 = ReadSphere(In);

	In.close();
	
	PrintSphere(s1,1);
	PrintSphere(s2,2);

	ofstream Out = ofstream("output.txt");
	if(IsSphereContect(s1,s2))
	{
		Out<<"YES";
		printf("Сферы пересикаются\n");
	}else{
		Out<<"NO";
		printf("Сферы не пересикаются\n");
	}
	
	Out.close();
	return EXIT_SUCCESS;
}

bool IsSphereContect(Sphere s1, Sphere s2)
{
	return sqrt((s2.X-s1.X)^2+(s2.Y-s1.Y)^2) <= (s1.R+s2.R);
}

void PrintSphere(Sphere s, int numder)
{
	printf("Сфера %i: (%i,%i) Радиус = %i\n", numder, s.X,s.Y,s.R);
}

Sphere ReadSphere(ifstream &stream)
{
	Sphere s;
	stream>>s.R;
	stream>>s.Y;
	stream>>s.X;
	return s;
}
