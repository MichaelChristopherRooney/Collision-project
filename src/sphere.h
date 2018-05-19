#pragma once

#include <stdint.h>

// Velocity is given as metres per second
// Position is given in metres and is the center of the sphere.
// For now assuming all spheres have the same radius
struct sphere_s {
	double x_vel;
	double y_vel;
	double z_vel;
	double x_pos;
	double y_pos;
	double z_pos;
	double radius;
};