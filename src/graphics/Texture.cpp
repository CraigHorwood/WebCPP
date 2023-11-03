#include "Texture.h"
#include "GLFW/glfw3.h"
#include "lodepng.h"
#include <iostream>

using namespace std;

Texture::Texture(const char* path) {
	// TODO: File I/O
	vector<unsigned char> pixels;
	unsigned int error = lodepng::decode(pixels, width, height, path);
	if (error) {
		cout << "Error " << error << ": " << lodepng_error_text(error) << endl;
		width = 256;
		height = 256;
		pixels.clear();
		pixels.reserve(width * height * 4);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				const int offs = (x + y * width) << 2;
				const unsigned char br = (((x >> 5) + (y >> 5)) & 1) == 0 ? 127 : 200;
				pixels[offs] = br;
				pixels[offs + 1] = br;
				pixels[offs + 2] = br;
				pixels[offs + 3] = 255;
			}
		}
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
}

Texture::~Texture() {
	glDeleteTextures(1, &texture);
}