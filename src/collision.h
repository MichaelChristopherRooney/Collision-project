#pragma once

#include <stdbool.h>

#include "sphere.h"

double find_collision_time_spheres(const struct sphere_s *s1, const struct sphere_s *s2, bool *collide);
double find_collision_time_grid(const struct sphere_s *s, bool *collide);
void apply_bounce_between_spheres(struct sphere_s *s1, struct sphere_s *s2);