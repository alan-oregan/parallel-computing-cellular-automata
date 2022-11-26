#include "declarations.h"

void initialize_world(CELL** world, CELL** newWorld){

    int i, j;
    unsigned char cell_status;

    // assign memory with malloc
    for(i = 0; i < SIM_SIZE; i++){
        world[i] = (CELL*)malloc(SIM_SIZE*sizeof(CELL));
        newWorld[i] = (CELL*)malloc(SIM_SIZE*sizeof(CELL));
    }

    // initialise values to 0
    for (i = 0; i < SIM_SIZE; i++) {
        for (j = 0; j < SIM_SIZE; j++) {
            world[i][j].duration = 0;
            cell_status = SUSCEPTIBLE;
            if (i == INITIAL_INFECTION_ROW && INITIAL_EXPOSED_NUMBER > j) {
                cell_status = EXPOSED;
            }
            world[i][j].status = cell_status;
            newWorld[i][j] = world[i][j];
            #if (DEBUG > 1)
                printf("%2c.%2d ", newWorld[i][j].status, newWorld[i][j].duration);
            #endif
        }
        #if (DEBUG > 1)
            printf("\n");
        #endif
    }
}
