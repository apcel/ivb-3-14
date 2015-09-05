#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define d_min 1
#define d_max 9

static double m1[] = { 1., 4., 2., 3. };
static double m2[] = { 4., 9. };
static double m3[] = { 1., 2., 3., 1., 2., 3. };

double
c(double m[], int n) {
	double result = 1;
	for (int i = 0; i < n; ++i) {
		if (m[i] <= d_max && m[i] >= d_min)
			result *= m[i];
	}
	return result;
}

int
main()
{
	double r1 = c(m1, sizeof(m1) / sizeof(m1[0]));
	double r2 = c(m2, sizeof(m2) / sizeof(m2[0]));
	double r3 = c(m3, sizeof(m3) / sizeof(m3[0]));

	if (r1 == r2)
		fprintf(stdout, "Matrix1 == Matrix2\n");
	if (r1 == r3)
		fprintf(stdout, "Matrix1 == Matrix3\n");
	if (r2 == r3)
		fprintf(stdout, "Matrix2 == Matrix3\n");

	system("pause");
	return 0;
}