#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

using namespace std;

int main() {
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	for (size_t i = 0; i < 50; i++)
	{
		cout << (int)data[i] << endl;
	}

	while (true)
	{

	}
}