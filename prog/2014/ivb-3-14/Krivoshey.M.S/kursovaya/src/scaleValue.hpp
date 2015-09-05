#include "hendel.h"

#ifndef __scaleVal
	#define __scaleVal
	/// <summary>1:1px</summary>
	#define scaleValueType_absolute 0
	/// <summary>1:ViewportSize</summary>
	#define scaleValueType_window 1
	class scaleValue
	{
	public:
		int type;
		vec2 value;
		vec2 get(int type);
		scaleValue();
		scaleValue(int Type, vec2 Value);
		scaleValue(int Type, int x, int y);
		static scaleValue fromString(char * data);
	};
#endif