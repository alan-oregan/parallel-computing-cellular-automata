#include "declarations.h"

int main() {
    int i;
    CELL *world[SIM_SIZE];
    CELL *newWorld[SIM_SIZE];

    for(i = 0; i < SIM_SIZE; i++){
        world[i] = (CELL *)malloc(SIM_SIZE*sizeof(CELL));
        newWorld[i] = (CELL *)malloc(SIM_SIZE*sizeof(CELL));
    }

    FILE *population_file = fopen("population.csv", "w");

    // add header to csv
    fprintf(population_file, "Iteration,Population Susceptible,Population Exposed,Population Infected,Population Removed\n");

    // initialise world
    initialize_world(world);

    // output generation 0
    output_to_file(world, 0, population_file);

    memcpy(newWorld, world, SIM_SIZE * SIM_SIZE * sizeof(struct cell));

    float chance;
    int iteration, row, col;

    for (iteration = 1; iteration <= GEN_LENGTH; iteration++) {

        for (row = 0; row < SIM_SIZE; row++) {
            for (col = 0; col < SIM_SIZE; col++) {
                switch (world[row][col].status) {
                    case SUSCEPTIBLE:
                        chance = check_neighbours(world, row, col);

                        if ((float)rand()/(float)RAND_MAX < chance) {
                            newWorld[row][col].status = EXPOSED;
                            newWorld[row][col].duration = 0;
                        } else {
                            newWorld[row][col].status = SUSCEPTIBLE;
                            newWorld[row][col].duration = 0;
                        }
                        break;

                    case EXPOSED:
                        if (world[row][col].duration == EXPOSED_DURATION) {
                            newWorld[row][col].status = INFECTED;
                            newWorld[row][col].duration = 0;
                        }
                        break;

                    case INFECTED:
                        if (world[row][col].duration == INFECTED_DURATION) {
                            newWorld[row][col].status = REMOVED;
                            newWorld[row][col].duration = 0;
                        }
                        break;

                    case REMOVED:
                        if (world[row][col].duration == REMOVED_DURATION) {
                            newWorld[row][col].status = SUSCEPTIBLE;
                            newWorld[row][col].duration = 0;
                        }
                        break;
                }

                if (world[row][col].status != SUSCEPTIBLE) {
                    newWorld[row][col].duration++;
                }
            }
        }

        if (iteration % OUTPUT_SAMPLE_SIZE == 0) {
            output_to_file(newWorld, iteration, population_file);
        }

        memcpy(world, newWorld, SIM_SIZE*SIM_SIZE*sizeof(world[0][0]));
    }
    output_to_file(newWorld, iteration, population_file);

    fclose(population_file);

    for(i = 0; i < SIM_SIZE; i++){
        free(world[i]);
        free(newWorld[i]);
    }

    return 0;
}
