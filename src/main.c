#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

void run_tests();

int main(void) {
	init_grid();
	update_grid();
	//run_tests();
	printf("Press enter to exit...\n");
	getchar();
	return 0;
}
