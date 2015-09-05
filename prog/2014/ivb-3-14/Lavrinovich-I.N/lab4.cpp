#include <fstream>

int
main()
{
	std::ifstream in("input.txt");

	int len;
	in >> len;
	len--;

	int* data = new int[len*2];
	for (int i = 0; i < len; i++) {
		in >> data[i];
		data[len + i] = data[i];
	}

	in.close();

	int i;
	for (i = 1; i < len; i++) {
		bool done = true;
		for (int n = 0; n < len; n++) {
			if (data[i + n] != data[n]) {
				done = false;
				break;
			}
		}
		if (done)
			break;
	}

	std::ofstream out("output.txt");
	out << i;
	out.close();

	delete data;
	return EXIT_SUCCESS;
}
