#include "declarations.h"

CELL neighbour;

float check_neighbours(CELL **world, int row, int col) {
    float chance = 0.0;
    int row_offset[8] = { 0,  0, -1,  1,  1,  1, -1, -1};
    int col_offset[8] = {-1,  1,  0,  0, -1,  1, -1,  1};

    for(int i = 0; i < NEIGHBOUR_COUNT; i++) {
        neighbour = world[(row + row_offset[i] % SIM_SIZE + SIM_SIZE) % SIM_SIZE][(col + col_offset[i] % SIM_SIZE + SIM_SIZE) % SIM_SIZE];

        if (neighbour.status == EXPOSED) {
            chance += EXPOSED_INFECTION_CHANCE;
        } else if (neighbour.status == INFECTED) {
            chance += INFECTED_INFECTION_CHANCE;
        }
    }

    return chance;
}