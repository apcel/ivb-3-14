#include "hendel.h"

#ifndef __texmger
	#define __texmger
	struct  Texture
	{
		string name;
		GLuint uint;
	};
	class TextureManager
	{
		static std::vector<Texture*> textures;
	public:
		static Texture* load(string name);
		static GLuint CreateEmpty(GLint internalFormat, GLenum format, GLsizei width, GLsizei height);
	};
#endif