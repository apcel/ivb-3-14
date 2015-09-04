#include "hendel.h"

#ifndef __sheder
	#define __sheder
	class shader
	{
	public:
		int pass;
		string name;
		GLuint ProgramID;
		GLuint TextureID;
		GLuint Texture2ID;
		GLuint colorBackID;
		GLuint colorMultID;
		GLuint TransformID;
		GLuint diffuse_enableID;
		GLuint invertYID;

		~shader();
		shader();
		shader(string name, int pass);
	};
	class ShaderManager
	{
		static vector<shader*> shaders;
	public:
		static shader* load(string name, int pass = -1);
	};
#endif