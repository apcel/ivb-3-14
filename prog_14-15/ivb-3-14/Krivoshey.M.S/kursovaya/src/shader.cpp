#include "shader.hpp"

vector<shader*> ShaderManager::shaders;

shader*
ShaderManager::load(string name, int pass)
{
	for (auto i = shaders.begin(); i < shaders.end(); i++)
		if ((*i)->name == name && (*i)->pass == pass)
			return *i;

	shader * sh = new shader(name, pass);
	shaders.push_back(sh);
	return sh;
}

shader::shader(){}
shader::shader(string name, int pass)
{
	this->pass = pass;
	this->name = name;

	string path = "Data\\shader\\" + name + '\\';
	if (pass >= 0) {
		path += "pass";
		path += '0' + pass;
		path += '_';
	}

	string h1 = path + "vs.glsl";
	const char * vertex_file_path = h1.c_str();
	string h2 = path + "fs.glsl";
	const char * fragment_file_path = h2.c_str();

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("File not found '%s'.\n", vertex_file_path);
		getchar();
		return;
	}

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("Linking program error:\n%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	TransformID = glGetUniformLocation(ProgramID, "MVP");
	TextureID = glGetUniformLocation(ProgramID, "diffuse");
	Texture2ID = glGetUniformLocation(ProgramID, "map2");
	colorMultID = glGetUniformLocation(ProgramID, "colorMult");
	colorBackID = glGetUniformLocation(ProgramID, "colorBack");
	diffuse_enableID = glGetUniformLocation(ProgramID, "diffuse_enable");
	invertYID = glGetUniformLocation(ProgramID, "invert_y");
}

shader::~shader(){}