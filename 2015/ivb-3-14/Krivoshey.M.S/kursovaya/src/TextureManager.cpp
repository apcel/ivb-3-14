#include "TextureManager.hpp"

std::vector<Texture*> TextureManager::textures;

Texture*
TextureManager::load(string name)
{
	for (auto i = textures.begin(); i != textures.end(); i++)
		if (name == (*i)->name)
			return *i;

	Texture* t = new Texture();
	t->name = name;
	t->uint = loadDDS(name);
	textures.push_back(t);

	return t;
}

GLuint
TextureManager::CreateEmpty(GLint internalFormat, GLenum format, GLsizei width, GLsizei height)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);

	return texture;
}