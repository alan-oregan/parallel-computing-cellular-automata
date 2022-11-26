#include "declarations.h"

void output_to_file(CELL **world, int iteration, FILE *population_file){

    int population_susceptible = 0;
    int population_exposed = 0;
    int population_infected = 0;
    int population_removed = 0;

    char fileNameBuffer[100];
    FILE *dat_file;

    sprintf(fileNameBuffer, "%s/world_%d.dat", OUTPUT_FILE_DIR, iteration);
    dat_file = fopen(fileNameBuffer, "w");

    if (dat_file == NULL) {
        printf("Error creating '%s' does %s exist", fileNameBuffer, OUTPUT_FILE_DIR);
    }

    int i, j;
    signed char cell_status;

    for (i = 0; i < SIM_SIZE; i++) {
        for (j = 0; j < SIM_SIZE; j++) {
            cell_status = world[i][j].status;
            switch (cell_status) {
                case SUSCEPTIBLE:
                    population_susceptible++;
                    break;
                case EXPOSED:
                    population_exposed++;
                    break;
                case INFECTED:
                    population_infected++;
                    break;
                case REMOVED:
                    population_removed++;
                    break;
            }
            fprintf(dat_file, "%c", cell_status);
            #if (DEBUG > 2)
                printf("%c ", cell_status);
            #endif
        }
        fprintf(dat_file, "\n");
        #if (DEBUG > 2)
            printf("\n");
        #endif
    }
    #if (DEBUG > 2)
        printf("\n");
    #endif

    fprintf(
        population_file,
        "%d,%d,%d,%d,%d\n",
        iteration,
        population_susceptible,
        population_exposed,
        population_infected,
        population_removed
    );

    fclose(dat_file);
}
