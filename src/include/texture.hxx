#pragma once

#include "shader.hxx"
#include <cstdint>

#include <iostream>

class Texture {
	public:
	unsigned int id;

	int width;
	int height;
	int nrChannels;

	Texture(const char *texturePath, int format);

	void Bind(Shader *shader,  const char *name, uint32_t unit);
};