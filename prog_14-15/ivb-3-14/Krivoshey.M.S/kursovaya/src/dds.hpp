#include "hendel.h"

#ifndef __dds
	#define __dds
	#define FOURCC_DXT1 827611204
	#define FOURCC_DXT3 861165636
	#define FOURCC_DXT5 894720068
	#define FOURCC_ARGB 0
	
	GLuint loadDDS(string imagepath);
#endif