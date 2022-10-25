//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// macros
#define INITIAL_INFECTION_ROW   0
#define INITIAL_EXPOSED_NUMBER  1

#define SIM_SIZE            1000
#define GEN_LENGTH          100
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

// macros for #if statements
#define DEBUG               0 // greater than 2 for debug
#define GENERATION_OUTPUT   1 // 1 for showing the generation number as the program runs

// data structures
typedef struct cell {
    signed char status;
    signed char duration;
} CELL;

// Function prototypes
void initialize_world(CELL**, CELL**);
float check_neighbours(CELL**, int, int);
void output_to_file(CELL**, int, FILE*);
