#pragma once

#include <stdbool.h>

#include "sphere.h"

double find_collision_time_spheres(struct sphere_s *s1, struct sphere_s *s2, bool *collide);
double find_collision_time_grid(struct sphere_s *s);