#include "hendel.h"

#ifndef __laber
#define __laber
	struct charInfo
	{
		GLuint uv;
		unsigned char c;
		vec2 scale;
		int offestY;
	};
	class Laber : public Control
	{
		string text;
		bool center;
		float fontSize = 1;
	public:
		static GLuint defaultTexture;

		void setFontSize(float fontSize);
		float getFontSize();
		void setText(string text);
		string getText();
		void UpdateTransform(bool updateChildren);
		void setCenter(bool enable);
		bool isCenter();

		Laber();

		static void Init(string texturePath, string font);
	};
#endif