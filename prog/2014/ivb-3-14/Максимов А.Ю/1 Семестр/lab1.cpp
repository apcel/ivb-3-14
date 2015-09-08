#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef __WIN32__
#define _PAUSE "pause"
#else
#define _PAUSE "echo -n press enter to continue;read" //Smth like winPAUSE analog.
#endif

//  #define MATRIX1 4
//  #define MATRIX2 2
//  #define MATRIX3 6

static double m1[] = { 4., 1., 1., 1. };

static double m2[] = { 2., 1. };

static double m3[] = { 4., 4., 4., 4., 4., 4. };

static double 
calculate(double matrix[], int elements, const double part)
{

    int i;
    int n = 0;
    double min; //minimum
    
    
    
    for (i = 0; i < elements; ++i) {
        if ((matrix[i] > part) and ((matrix[i] < min) or ( n == 0 )) ) {
            min = matrix[i];
            ++n;
        }
    }
    return min == 0 || n == 0 ? 0 : min ;
}

int
main(int argc, char **argv)
{
    const double part = 1.;
    double mr1 = calculate(m1, sizeof(m1)/sizeof(m1[0]), part);
    double mr2 = calculate(m2, sizeof(m2)/sizeof(m2[0]), part);
    double mr3 = calculate(m3, sizeof(m3)/sizeof(m3[0]), part);
    
    if (mr1 != 0) {
        if (mr1 == mr2)
            fprintf(stdout, "MinOfMatrix1 == MinOfMatrix2\n");
        else 
            fprintf(stdout, "12neq\n");
        
        if (mr1 == mr3)
            fprintf(stdout, "MinOfMatrix1 == MinOfMatrix3\n");
        else 
            fprintf(stdout, "13neq\n");
        
    } 
    if (mr2 != 0) {        
        if (mr2 == mr3)
            fprintf(stdout, "MinOfMatrix2 == MinOfMatrix3\n");
        else 
            fprintf(stdout, "23neq\n");
    } else
        if (mr1 == 0)
            fprintf(stdout, "No matrix contain num > part\n");
    
    int IMTooLazyToUseWunusedresult = system(_PAUSE);
    
    return EXIT_SUCCESS;
}
