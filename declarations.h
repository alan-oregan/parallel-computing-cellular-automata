//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macros
#define INITIAL_INFECTION_ROW   0
#define INITIAL_EXPOSED_NUMBER  10

#define SIM_SIZE            10
#define GEN_LENGTH    10
#define OUTPUT_SAMPLE_SIZE  10

#define SUSCEPTIBLE         'S'
#define EXPOSED             'E'
#define INFECTED            'I'
#define REMOVED             'R'

#define EXPOSED_INFECTION_CHANCE    0.0625
#define INFECTED_INFECTION_CHANCE   0.125

#define EXPOSED_DURATION    7
#define INFECTED_DURATION   10
#define REMOVED_DURATION    90

#define NEIGHBOUR_COUNT     8

#define OUTPUT_FILE_DIR     "output"

#define DEBUG               0 // greater than 2 for debug

// data structures
struct cell {
    signed char status;
    signed char duration;
};

// functions
void initialize_world(struct cell (*world)[SIM_SIZE][SIM_SIZE]);
float check_neighbours(struct cell (*world)[SIM_SIZE][SIM_SIZE], int row, int col);
void output_to_file(struct cell (*world)[SIM_SIZE][SIM_SIZE], int iteration, FILE *population_file);
