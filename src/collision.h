#pragma once

#include <stdbool.h>

#include "sphere.h"

double find_collision_time_spheres(const struct sphere_s *s1, const struct sphere_s *s2, bool *collide);
double find_collision_time_grid(const struct sphere_s *s);