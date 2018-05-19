// This is the area in which the collisions take place. 
// Imagine the grid is a 3D box with all collisions taking place inside it.
// Normally x_start, y_start and z_start will all be 0, but the code is 
// built to work with other positive values.
// Note that all values here MUST be positive. 
struct grid_s {
	double x_start;
	double y_start;
	double z_start;
	double x_end;
	double y_end;
	double z_end;
};

struct grid_s *grid; // The grid used by the simulation