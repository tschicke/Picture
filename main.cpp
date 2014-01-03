/*
 * main.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: Tyler
 */

#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <stdlib.h>
#include "Noise.h"

void drawPixels(float * pixels, int width, int height);
float * movePixels(float * pixels, int width, int height);
float * createImage(int width, int height);

void glInit(int width, int height) {
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glOrtho(0, width, 0, height, -1, 1);
	//	glPixelZoom(10, 10);
}

int main() {
	int width = 1024, height = 1024;
	sf::Window window;
	window.create(sf::VideoMode(width, height, 32), "Picture");
	window.setFramerateLimit(60);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Glew failed to initialize\n";
		return 1;
	}

	glInit(width, height);

	float * pixels = createImage(width, height);

	bool running = true;
	while (running) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				running = false;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		pixels = movePixels(pixels, width, height);
		drawPixels(pixels, width, height);

		window.display();
	}

	delete pixels;
}

float * createImage(int width, int height) {
	Noise noise;
	float * pixels = new float[width * height * 3];

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int index = (x * height + y) * 3;
			float noiseVal1 = noise.smoothNoise2D((x - 512) / 32.f, (y - 512) / 32.f);
//			noiseVal1 = (noiseVal1 < 0.5 ? 0 : 1);
			float noiseVal2 = noise.smoothNoise2D(x / 32.f, y / 32.f);
//			noiseVal2 = (noiseVal2 < 0.5 ? 0 : 1);
			float noiseVal3 = noise.smoothNoise2D((x + 512) / 32.f, (y + 512) / 32.f);
//			noiseVal3 = (noiseVal3 < 0.5 ? 0 : 1);
//			std::cout << x / 17.f << '\n';
			pixels[index] = noiseVal1;
			pixels[index + 1] = noiseVal2;
			pixels[index + 2] = noiseVal3;
		}
	}

	return pixels;
}

float * movePixels(float * pixels, int width, int height) {
	Noise noise;
	static int statX = 0, statY = 0;
	statX -= 1;
	statY -= 1;
	for (int x = width - 1; x > 0; --x) {
		for (int y = height - 1; y > 0; --y) {
			int index = (x * height + y) * 3;
			int indexMinusOne = ((x - 1) * height + (y - 1)) * 3;
			pixels[index] = pixels[indexMinusOne];
			pixels[index + 1] = pixels[indexMinusOne + 1];
			pixels[index + 2] = pixels[indexMinusOne + 2];
		}
	}
	for (int x = 0; x < width; ++x) {
		int index = (x * height) * 3; //y = 0
		float r = noise.smoothNoise2D((x + statX - 512) / 32.f, (statY - 512) / 32.f);
		float g = noise.smoothNoise2D((x + statX) / 32.f, (statY) / 32.f);
		float b = noise.smoothNoise2D((x + statX + 512) / 32.f, (statY + 512) / 32.f);
		pixels[index] = r;
		pixels[index + 1] = g;
		pixels[index + 2] = b;
	}
	for (int y = 1; y < height; ++y) {
		int index = y * 3; //x = 0
		float r = noise.smoothNoise2D((statX - 512) / 32.f, (y + statY - 512) / 32.f);
		float g = noise.smoothNoise2D((statX) / 32.f, (y + statY) / 32.f);
		float b = noise.smoothNoise2D((statX + 512) / 32.f, (y + statY + 512) / 32.f);
		pixels[index] = r;
		pixels[index + 1] = g;
		pixels[index + 2] = b;
	}

	return pixels;
}

void drawPixels(float * pixels, int width, int height) {
	glRasterPos2f(0, 0);
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
}

