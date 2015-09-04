#include "dds.hpp"

GLuint
loadDDS(string imagepath)
{
	unsigned char header[124];

	FILE *fp;

	fp = fopen(imagepath.c_str(), "rb");
	if (fp == NULL) {
		printf("Error. Texture '%s' is not found.\n", imagepath.c_str());
		return -1;
	}

	char filecode[4];
	fread(filecode, 1, 4, fp);

	if (strncmp(filecode, "DDS ", 4) != 0) {
		printf("Error. Texture '%s' is not 'DDS' format.\n", imagepath.c_str());
		fclose(fp);
		return -1;
	}

	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	unsigned char * buffer;
	unsigned int bufsize;

	if (mipMapCount == 0) {
		printf("Error. Texture '%s' not have mip-map level.\n", imagepath.c_str());
		return -1;
	}

	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);

	fclose(fp);

	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	case FOURCC_ARGB:
		format = 0;
		break;
	default:
		printf("Error. Type texture '%s' is not supported.\n", imagepath.c_str());
		free(buffer);
		return -1;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if (format == 0) {
		for (unsigned int i = 0; i < bufsize; i += 4) {
			swap(buffer[i], buffer[i + 3]);
			swap(buffer[i + 1], buffer[i + 2]);
		}
	}

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); level++)	{
		unsigned int size;

		if (format != 0) {
			size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);
		} else {
			size = width*height * 4;
			glTexImage2D(GL_TEXTURE_2D, level, 4, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer + offset);
		}

		offset += size;
		width /= 2;
		height /= 2;
	}

	free(buffer);

	printf("Load texture '%s'\n", imagepath.c_str());
	return textureID;
}