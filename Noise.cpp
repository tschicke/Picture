/*
 * Noise.cpp
 *
 *  Created on: Mar 9, 2013
 *      Author: Tyler
 */

#include "Noise.h"
#include <math.h>

#include <iostream>

Noise::Noise() {
}

Noise::~Noise() {
}

double Noise::smoothNoise2D(double x, double y) {
	int floorx = floor(x); //This is kinda a cheap way to floor a double integer.
	int floory = floor(y);
	double s, t, u, v; //Integer declaration
	s = noise2D(floorx, floory);
	t = noise2D(floorx + 1, floory);
	u = noise2D(floorx, floory + 1); //Get the surrounding pixels to calculate the transition.
	v = noise2D(floorx + 1, floory + 1);

	float int1 = interpolate(s, t, x - floorx); //Interpolate between the values.
	float int2 = interpolate(u, v, x - floorx); //Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.

	return interpolate(int1, int2, y - floory);
}

double Noise::smoothNoise3D(double x, double y, double z) { //TODO make noise function better
	int floorx = floor(x); //This is kinda a cheap way to floor a double integer.
	int floory = floor(y);
	int floorz = floor(z);
	double o, p, q, r, s, t, u, v; //Integer declaration
	o = noise3D(floorx, floory, floorz + 1);
	p = noise3D(floorx + 1, floory, floorz + 1);
	q = noise3D(floorx, floory + 1, floorz + 1); //Get the surrounding pixels to calculate the transition.
	r = noise3D(floorx + 1, floory + 1, floorz + 1);
	s = noise3D(floorx, floory, floorz);
	t = noise3D(floorx + 1, floory, floorz);
	u = noise3D(floorx, floory + 1, floorz); //Get the surrounding pixels to calculate the transition.
	v = noise3D(floorx + 1, floory + 1, floorz);

	float int1 = interpolate(s, t, x - floorx); //Interpolate between the values.
	float int2 = interpolate(u, v, x - floorx); //Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
	float int3 = interpolate(o, p, x - floorx);
	float int4 = interpolate(q, r, x - floorx);

	float int5 = interpolate(int1, int2, y - floory);
	float int6 = interpolate(int3, int4, y - floory);

	return interpolate(int5, int6, z - floorz);
}

double Noise::interpolate(double a, double b, double x) {
	double ft = x * 3.1415927;
	double f = (1.0 - cos(ft)) * 0.5;
	return a * (1.0 - f) + b * f;
}

double Noise::noise2D(int x, int y) {
	int n = x + y * 43;
	n = (n << 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double) nn / 1073741824.0);

//	double number = (((x * 60493 + y * 72091 + 104369) ^ 104729) % 500000) / 500000.f;

//	return number;
}

double Noise::noise3D(int x, int y, int z) {
	int n = x + y * 43 + z * 49;
	n = (n << 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double) nn / 1073741824.0);
}

