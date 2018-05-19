#include <float.h>
#include <math.h>

#include "collision.h"
#include "grid.h"

static double get_xyz_vector_magnitude(double x, double y, double z) {
	return sqrt((x*x) + (y*y) + (z*z));
}

// Given two sets of xyz values returns the dot product
static double get_xyz_vector_dot_product(double x1, double x2, double y1, double y2, double z1, double z2) {
	return (x1 * x2) + (y1 * y2) + (z1 * z2);
}

// Given the already computed dot product returns the angle between two xyz vectors.
static double get_shortest_angle_between_xyz_vectors(double dp, double mag1, double mag2) {
	double cos_inv = dp / (mag1 * mag2);
	return acos(cos_inv);
}

// Finds the time at which the two spheres will collide.
// If the spheres will not collide on their current paths then returns 0 and 
// sets the collide parameter to false.
// Note this assumes that the velocity of both particles is constant before the collision.
// Performs the following tests to see if the spheres will collide.
// First test:
//	1) Obtain velocity of s1 relative to s2.
//	2) Obtain position of s2 relative to s1.
//	3) If the shortest angle between these two vectors is >= 90 then the 
//	   spheres will not collide on their current paths so return.
// Second test:
//	1) Using relative velocity and position find the shortest distance 
//	   between the two points along their current paths.
//	2) If this is larger than the sum of their radii then the spheres will 
//	   not collide so return.
// If these tests pass then we know the spheres will collide. 
// We then have to figure out the actual point of collision, as the shortest
// distance will very likely be when the spheres pass through one another.
// Trigonometry is used to figure out where the spheres collide.
// TODO: better comments on trig part
double find_collision_time_spheres(struct sphere_s *s1, struct sphere_s *s2, bool *collide) {
	double x_rel_vel = s1->x_vel - s2->x_vel;
	double y_rel_vel = s1->y_vel - s2->y_vel;
	double z_rel_vel = s1->z_vel - s2->z_vel;
	double x_rel_pos = s2->x_pos - s1->x_pos;
	double y_rel_pos = s2->y_pos - s1->y_pos;
	double z_rel_pos = s2->z_pos - s1->z_pos;
	double dp = get_xyz_vector_dot_product(x_rel_vel, x_rel_pos, y_rel_vel, y_rel_pos, z_rel_vel, z_rel_pos);
	double vel_vec_mag = get_xyz_vector_magnitude(x_rel_vel, y_rel_vel, z_rel_vel);
	double pos_vec_mag = get_xyz_vector_magnitude(x_rel_pos, y_rel_pos, z_rel_pos);
	double angle = get_shortest_angle_between_xyz_vectors(dp, vel_vec_mag, pos_vec_mag);
	if (angle >= 3.14159265358979323846 / 2.0) { //check if >= 90 degrees (note angle is in radians)
		*collide = false;
		return 0;
	}
	double r_total = s1->radius + s2->radius;
	double shortest_dist = sin(angle) * pos_vec_mag;
	if (shortest_dist > r_total) {
		*collide = false;
		return false;
	}
	double d = sqrt((pos_vec_mag * pos_vec_mag) - (shortest_dist * shortest_dist));
	double t = sqrt((r_total * r_total) - (shortest_dist * shortest_dist));
	double dist_to_col = d - t;
	*collide = true;
	return  dist_to_col / vel_vec_mag;
}

// Finds the time taken to cross the boundary on the specified axis in the grid.
// axis_vel and axis_pos are the velocity/position of the sphere on that axis.
static double find_time_to_cross_boundary(double bound_start, double bound_end, double axis_vel, double axis_pos, double radius) {
	double dist = 0;
	if (axis_vel > 0) {
		dist = bound_end - axis_pos - radius;
	} else {
		dist = bound_start - axis_pos + radius;
	}
	return dist / axis_vel;
}

// Finds the time when the sphere will collide with the grid on its current path.
double find_collision_time_grid(struct sphere_s *s) {
	double time = DBL_MAX;
	if (s->x_vel != 0) {
		time = find_time_to_cross_boundary(grid->x_start, grid->x_end, s->x_vel, s->x_pos, s->radius);
	}
	if (s->y_vel != 0) {
		double y_time = find_time_to_cross_boundary(grid->y_start, grid->y_end, s->y_vel, s->y_pos, s->radius);
		if (y_time < time) {
			time = y_time;
		}
	}
	if (s->z_vel != 0) {
		double z_time = find_time_to_cross_boundary(grid->z_start, grid->z_end, s->z_vel, s->z_pos, s->radius);
		if (z_time < time) {
			time = z_time;
		}
	}
	return time;
}