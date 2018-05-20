#include <stdio.h>
#include <stdlib.h>

#include "collision.h"
#include "grid.h"
#include "sphere.h"

// Using hardcoded values for now
void init_grid() {
	grid = calloc(1, sizeof(grid));
	grid->x_start = 0.0;
	grid->y_start = 0.0;
	grid->z_start = 0.0;
	grid->x_end = 50.0;
	grid->y_end = 50.0;
	grid->z_end = 50.0;
}

void run_tests();

int main(void) {
	init_grid();
	run_tests();
	// Some hardcoded values for testing for now.
	struct sphere_s s2 = { { -1.0, 1.0, -1.0 }, { 20.0, 10.0, 10.0 }, 1.0, 1.0 };
	struct sphere_s s1 = { { 0.0, 1.0, -1.0 }, { 10.0, 10.0, 10.0 }, 1.0, 1.0 };
	bool collide = false;
	double t1 = find_collision_time_spheres(&s1, &s2, &collide);
	double t2 = find_collision_time_grid(&s1);
	double t3 = find_collision_time_grid(&s2);
	return 0;
}
