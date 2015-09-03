#include "scaleValue.hpp"

vec2 scaleValue::get(int Type)
{
	if (Type == type)
		return value;
	else {
		if (Type == scaleValueType_absolute)
			return Control::screenToPixel(value);
		if (Type == scaleValueType_window)
			return Control::pixelToScreen(value);
	}
	return value;
}

scaleValue::scaleValue()
{
}

scaleValue::scaleValue(int Type, int x, int y) :scaleValue::scaleValue(Type, vec2(x, y))
{
}

scaleValue::scaleValue(int Type, vec2 Value)
{
	type = Type;
	value = Value;
}

scaleValue scaleValue::fromString(char * data)
{
	int lim = 3;
	char**buff = new char*[3];
	int len = strlen(data);
	int offest = 0;
	int F = 0;
	scaleValue sv;
	data[len] = ' ';

	for (int i = 0; i < lim; i++)
		buff[i] = new char[len];

	for (int i = 0; i <= len; i++){
		if (data[i] == ' ')	{
			buff[F][offest] = 0;
			offest = 0;
			if (++F > lim)
				return sv;
		}
		else
			buff[F][offest++] = data[i];
	}

	sv.type = atoi(buff[0]);
	sv.value = vec2(atoi(buff[1]), atoi(buff[2]));

	for (int i = 0; i < lim; i++)
		delete[] buff[i];
	delete[] buff;

	data[len] = 0;

	return sv;
}