#include <stdio.h>
#include <stdlib.h>

#include "collision.h"
#include "grid.h"
#include "sphere.h"

static void test_1(char *test_name) {
	int error = 0;
	struct sphere_s s2 = { { -1.0, 0.0, 0.0 }, { 20.0, 10.0, 10.0 }, 1.0, 1.0 };
	struct sphere_s s1 = { { 0.0, 0.0, 0.0 }, { 10.0, 10.0, 10.0 }, 1.0, 1.0 };
	bool collide = false;
	double t = find_collision_time_spheres(&s1, &s2, &collide);
	if (collide == false) {
		printf("%s: FAILED. Collide variable is false but should be true\n", test_name);
		error = 1;
	}
	if (t != 8.0) {
		printf("%s: FAILED. Time of collision should be 8.0 but is %f\n", test_name, t);
		error = 1;
	}
	if (error == 0) {
		printf("%s: PASSED.\n", test_name);
	}

}
void run_tests() {
	test_1("Test one");
}