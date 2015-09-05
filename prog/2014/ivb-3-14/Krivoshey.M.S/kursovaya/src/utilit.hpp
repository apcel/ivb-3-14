#include "hendel.h"

#ifndef __utilit
	#define __utilit
	/// <summary>√енирирует случайное число в заданом диапозоне</summary>
	float GetRandom(float min, float max);
	vec4 vec4fromString(char * data);
	vec2 vec2fromString(char * data);
	/// <summary>ќпредел€ет принадлежит ли точка pos области bound</summary>
	bool containt(vec4 bound, vec2 pos);
	/// <summary>ќкругл€ет float по правилам округлени€</summary>
	int float2int(float a);
	/// <summary>√енирирует и загружает в пам€ть count*count текстурных координат</summary>
	GLuint* BuildUV(int count);
	/// <summary>√енирирует и загружает в пам€ть масив с uv координатами</summary>
	GLuint BuildUV(string v4);

	template <typename ValueType>
	struct range {
		ValueType start, end;
		range() : start(0), end(0){}
		range(ValueType a) : start(a), end(a){}
		range(ValueType a, ValueType b) : start(a), end(b){}
		ValueType operator()()
		{
			if (end == start)
				return start;
			else
				return start + (end - start) * GetRandom(0, 1);
		}
	};

	class IDelegate{};

	template <typename par1>
	class Delegate
	{
	public:
		struct Key
		{
			IDelegate* object;
			void(IDelegate::*metod)(par1 * p1);
		};
		vector<Key> keys;

		Delegate(){}
		Delegate(IDelegate* object, void(IDelegate::*metod)(par1 * p1))
		{
			operator+=({ object, metod });
		}

		void operator += (Key key)
		{
			keys.push_back(key);
		}

		void operator -= (Key key)
		{
			for (auto i = keys.begin(); i != keys.end(); i++)
				if (i->object == key.object && i->metod == key.metod) {
					keys.erase(i);
					return;
				}
		}

		void operator () (par1 * p1)
		{
			for (auto i = keys.begin(); i != keys.end(); i++)
				((i->object)->*(i->metod))(p1);
		}
	};
#endif