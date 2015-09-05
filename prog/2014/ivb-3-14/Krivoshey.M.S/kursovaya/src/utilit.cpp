#include "utilit.hpp"

vec4
vec4fromString(char * data)
{
	int lim = 4;
	char**buff = new char*[lim];
	int len = strlen(data);
	int offest = 0;
	int F = 0;
	vec4 vec;
	data[len] = ' ';

	for (int i = 0; i < lim; i++)
		buff[i] = new char[len];

	for (int i = 0; i <= len; i++) {
		if (data[i] == ' ') {
			buff[F][offest] = 0;
			offest = 0;
			if (++F > lim)
				return vec;
		} else
			buff[F][offest++] = data[i];
	}

	vec.r = (float)atof(buff[0]);
	vec.g = (float)atof(buff[1]);
	vec.b = (float)atof(buff[2]);
	vec.a = (float)atof(buff[3]);

	for (int i = 0; i < lim; i++)
		delete[] buff[i];
	delete[] buff;

	data[len] = 0;

	return vec;
}

vec2
vec2fromString(char * data)
{
	int lim = 2;
	char**buff = new char*[lim];
	int len = strlen(data);
	int offest = 0;
	int F = 0;
	vec2 vec;
	data[len] = ' ';

	for (int i = 0; i < lim; i++)
		buff[i] = new char[len];

	for (int i = 0; i <= len; i++) {
		if (data[i] == ' ') {
			buff[F][offest] = 0;
			offest = 0;
			if (++F > lim)
				return vec;
		}
		else
			buff[F][offest++] = data[i];
	}

	vec.x = (float)atof(buff[0]);
	vec.y = (float)atof(buff[1]);

	for (int i = 0; i < lim; i++)
		delete[] buff[i];
	delete[] buff;

	data[len] = 0;

	return vec;
}

bool
containt(vec4 bound, vec2 pos)
{
	return	bound.x <= pos.x &&
			pos.x <= bound.z && 
			bound.y <= pos.y && 
			pos.y <= bound.w;
}

float
GetRandom(float M, float N)
{
	return (float)(M + (rand() / (RAND_MAX / (N - M))));
}

GLuint*
BuildUV(int count)
{
	int real = count;
	int l = std::sqrt(count);
	if (l*l != count) {
		l++;
		count = l*l;
	}

	GLuint *list = new GLuint[real];
	float step = 1 / (float)l;
	float uv[] = {
		0.0f, 0.0f,
		step, 0.0f,
		step, step,

		0.0f, 0.0f,
		step, step,
		0.0f, step,
	};

	for (int x = 0, i = 0; x < l; x++) {
		for (int y = 0; y < l && i < real; y++, i++) {
			glGenBuffers(1, &list[i]);
			glBindBuffer(GL_ARRAY_BUFFER, list[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
			for (int n = 0; n < 12; n += 2)
				uv[n] += step;
		}
		for (int n = 1; n < 12; n += 2)
			uv[n] += step;
	}

	return list;
}

GLuint
BuildUV(string v4)
{
	vec4 data = vec4fromString((char *)v4.c_str());
	GLuint o;

	float uv[] = {
		data.x, data.y,
		data.z, data.y,
		data.z, data.w,

		data.x, data.y,
		data.z, data.w,
		data.x, data.w,
	};

	glGenBuffers(1, &o);
	glBindBuffer(GL_ARRAY_BUFFER, o);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

	return o;
}

int
float2int(float a)
{
	int f = floor(a);
	return (a - f < 0.5) ? f : ceil(a);
}