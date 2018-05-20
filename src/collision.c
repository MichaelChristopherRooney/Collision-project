#include <float.h>
#include <math.h>

#include "collision.h"
#include "grid.h"
#include "vector_3.h"

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
double find_collision_time_spheres(const struct sphere_s *s1, const struct sphere_s *s2, bool *collide) {
	struct vector_3_s rel_vel = { s1->vel.x - s2->vel.x, s1->vel.y - s2->vel.y, s1->vel.z - s2->vel.z };
	struct vector_3_s rel_pos = { s2->pos.x - s1->pos.x, s2->pos.y - s1->pos.y, s2->pos.z - s1->pos.z };
	double dp = get_vector_3_dot_product(&rel_vel, &rel_pos);
	double vel_vec_mag = get_vector_3_magnitude(&rel_vel);
	double pos_vec_mag = get_vector_3_magnitude(&rel_pos);
	double angle = get_shortest_angle_between_vector_3(dp, vel_vec_mag, pos_vec_mag);
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
static double find_time_to_cross_boundary(const double bound_start, const double bound_end, const double axis_vel, const double axis_pos, const double radius) {
	double dist = 0;
	if (axis_vel > 0) {
		dist = bound_end - axis_pos - radius;
	} else {
		dist = bound_start - axis_pos + radius;
	}
	return dist / axis_vel;
}

// Finds the time when the sphere will collide with the grid on its current path.
double find_collision_time_grid(const struct sphere_s *s) {
	double time = DBL_MAX;
	if (s->vel.x != 0) {
		time = find_time_to_cross_boundary(grid->x_start, grid->x_end, s->vel.x, s->pos.x, s->radius);
	}
	if (s->vel.y != 0) {
		double y_time = find_time_to_cross_boundary(grid->y_start, grid->y_end, s->vel.y, s->pos.y, s->radius);
		if (y_time < time) {
			time = y_time;
		}
	}
	if (s->vel.z != 0) {
		double z_time = find_time_to_cross_boundary(grid->z_start, grid->z_end, s->vel.z, s->pos.z, s->radius);
		if (z_time < time) {
			time = z_time;
		}
	}
	return time;
}