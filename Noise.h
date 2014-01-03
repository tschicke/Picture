/*
 * Noise.h
 *
 *  Created on: Mar 9, 2013
 *      Author: Tyler
 */

#ifndef NOISE_H_
#define NOISE_H_

class Noise {
public:
	Noise();
	virtual ~Noise();
	double smoothNoise2D(double x, double y);
	double smoothNoise3D(double x, double y, double z);
	double noise2D(int x, int y);
	double noise3D(int x, int y, int z);
private:
	double interpolate(double a, double b, double x);
};

#endif /* NOISE_H_ */
