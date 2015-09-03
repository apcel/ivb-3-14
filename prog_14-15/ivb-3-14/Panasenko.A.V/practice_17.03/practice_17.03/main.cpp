#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
using namespace std;

int
main() {
	class obj {
	public :
		int ob;
		numb(int gg) :value::numb(0) {};
		void * operator new (size_t size) {
			return malloc(size);
		}
		void operator delete (void *gg) {
			free(gg);
		}
		void operator delete[](void *gg) {
			free(gg);
		}
		double operator + (const double *num) {
			return *this + num;
		}
		double operator == (double *num) {
			return ob == num->obj;
		}
		
	};
}
