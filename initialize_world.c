#include "declarations.h"

void initialize_world(struct cell (*world)[SIM_SIZE][SIM_SIZE]){

    int i, j;
    unsigned char cell_status;

    for (i = 0; i < SIM_SIZE; i++) {
        for (j = 0; j < SIM_SIZE; j++) {
            world[i][j]->duration = 0;
            cell_status = SUSCEPTIBLE;
            if (i == INITIAL_INFECTION_ROW && INITIAL_EXPOSED_NUMBER > j) {
                cell_status = EXPOSED;
            }
            world[i][j]->status = cell_status;
            printf("%d ", world[i][j]->status);
        }
        printf("\n");
    }
}