/*
Author: @alan-oregan
*/
#include "../common/declarations.h"

int main() {

    #if (TIMER)
        double start, finish, elapsed;
        GET_TIME(start);
    #endif

    CELL *world[SIM_SIZE];
    CELL *newWorld[SIM_SIZE];

    FILE *population_file = fopen("population.csv", "w");

    if (population_file == NULL) {
        printf("Error: creating population.csv");
        exit(1);
    }

    srand((unsigned int)time(NULL));

    // add header to csv
    fprintf(population_file, "Generation,Population Susceptible,Population Exposed,Population Infected,Population Removed\n");

    // initialise world
    initialize_world(world, newWorld);

    #if (GENERATION_OUTPUT)
        printf("\rGeneration %d/%d", 0, GEN_LENGTH-1);
    #endif

    // output generation 0
    output_to_file(world, 0, population_file);

    float chance;
    float exposureChance = (float)rand() / (float)RAND_MAX;
    int generation, row, col;

    for (generation = 1; generation < GEN_LENGTH; generation++) {
        for (row = 0; row < SIM_SIZE; row++) {
            for (col = 0; col < SIM_SIZE; col++) {
                switch (world[row][col].status) {
                    case SUSCEPTIBLE:
                        chance = check_neighbours(world, row, col);

                        if (exposureChance < chance) {
                            newWorld[row][col].status = EXPOSED;
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

                // Everything has a duration except for SUSCEPTIBLE
                if (world[row][col].status != SUSCEPTIBLE) {
                    newWorld[row][col].duration++;
                }
            }
        }

        // output to file every sample size generation
        if (generation % OUTPUT_SAMPLE_SIZE == 0) {
            output_to_file(newWorld, generation, population_file);
        }

        // update world with newWorld
        for(row = 0; row < SIM_SIZE; row++){
            memcpy(world[row], newWorld[row], SIM_SIZE*sizeof(CELL));
        }

        #if (GENERATION_OUTPUT)
            printf("\rGeneration %d/%d, Exposure chance: %f", generation, GEN_LENGTH-1, exposureChance);
        #endif

        exposureChance = (float)rand() / (float)RAND_MAX;
    }

    // output final generation regardless of sample size
    output_to_file(newWorld, GEN_LENGTH, population_file);

    printf("\nSee /output directory and population.csv file for results\n");

    // close files and free memory
    fclose(population_file);

    for (row = 0; row < SIM_SIZE; row++) {
        free(world[row]);
        free(newWorld[row]);
    }

    #if (TIMER)
        GET_TIME(finish);

        elapsed = finish - start;
        printf("The code to be timed took %lf seconds\n", elapsed);
    #endif

    return 0;
}
