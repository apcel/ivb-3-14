#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>


#define MATRIX1 4
#define MATRIX2 2
#define MATRIX3 6

static double m1[] = { 1., 1., 1., 1. };

static double m2[] = { 1., 1. };

static double m3[] = { 4., 4., 4., 4., 4., 4. };

static double 
calculate(double matrix[], int elements, const double part)
{
    int i;
    int n = 0;

    for (i = 0; i < elements; ++i) {
        if (matrix[i] < part) 
        ++n;
    }
    return n;
}

int
main(int argc, char **argv)
{
    const double part = 4.;
    double mr1 = calculate(m1, MATRIX1, part);
    double mr2 = calculate(m2, MATRIX2, part);
    double mr3 = calculate(m3, sizeof(m3)/sizeof(m3[0]), part);

    if ((mr1 > mr2) && (mr1 > mr3))
        fprintf (stdout, "Matrix1\n");
    if ((mr2 > mr1) && (mr2 > mr3))
        fprintf (stdout, "Matrix2\n");
    if ((mr3 > mr1) && (mr3 > mr2))
        fprintf (stdout, "Matrix3\n");
    system("pause");
    return EXIT_SUCCESS;
}
