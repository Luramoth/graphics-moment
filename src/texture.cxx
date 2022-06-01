#define STB_IMAGE_IMPLEMENTATION

#include "include/texture.hxx"
#include "include/stb_image.h"
#include "include/glad/glad.h"

#include <iostream>

Texture::Texture(const char *texturePath, int format) {
	//generate the texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	float boarderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, boarderColor);

	// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load the texture
	stbi_set_flip_vertically_on_load(true);

	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	// check if we actually got the data
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	} else {
		std::cout << "error loading image data!\n";
	}

	stbi_image_free(data);
}

void Texture::Bind(Shader *shader, const char *name, uint32_t unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);

	shader->setInt(name, unit);
}