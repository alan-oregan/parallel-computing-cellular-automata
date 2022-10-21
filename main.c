#include "declarations.h"

int main() {
    struct cell (*world)[SIM_SIZE][SIM_SIZE];
    struct cell (*newWorld)[SIM_SIZE][SIM_SIZE];

    world = calloc(SIM_SIZE * SIM_SIZE, sizeof(struct cell));
    newWorld = calloc(SIM_SIZE * SIM_SIZE, sizeof(struct cell));

    FILE *population_file = fopen("population.csv", "w");

    // add header to csv
    fprintf(population_file, "Iteration,Population Susceptible,Population Exposed,Population Infected,Population Removed\n");

    // initialise world
    initialize_world(world); // TODO fix this as it breaks here for some reason

    // output generation 0
    output_to_file(world, 0, population_file);

    memcpy(newWorld, world, SIM_SIZE * SIM_SIZE * sizeof(struct cell));

    float chance;
    int iteration, row, col;

    for (iteration = 1; iteration <= GEN_LENGTH; iteration++) {

        for (row = 0; row < SIM_SIZE; row++) {
            for (col = 0; col < SIM_SIZE; col++) {
                switch (world[row][col]->status) {
                    case SUSCEPTIBLE:
                        chance = check_neighbours(world, row, col);

                        if ((float)rand()/(float)RAND_MAX < chance) {
                            newWorld[row][col]->status = EXPOSED;
                            newWorld[row][col]->duration = 0;
                        } else {
                            newWorld[row][col]->status = SUSCEPTIBLE;
                            newWorld[row][col]->duration = 0;
                        }
                        break;

                    case EXPOSED:
                        if (world[row][col]->duration == EXPOSED_DURATION) {
                            newWorld[row][col]->status = INFECTED;
                            newWorld[row][col]->duration = 0;
                        }
                        break;

                    case INFECTED:
                        if (world[row][col]->duration == INFECTED_DURATION) {
                            newWorld[row][col]->status = REMOVED;
                            newWorld[row][col]->duration = 0;
                        }
                        break;

                    case REMOVED:
                        if (world[row][col]->duration == REMOVED_DURATION) {
                            newWorld[row][col]->status = SUSCEPTIBLE;
                            newWorld[row][col]->duration = 0;
                        }
                        break;
                }

                if (world[row][col]->status != SUSCEPTIBLE) {
                    newWorld[row][col]->duration++;
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
    free(world);
    free(newWorld);

    return 0;
}