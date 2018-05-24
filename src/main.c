#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

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
	printf("Press enter to exit...\n");
	getchar();
	return 0;
}
