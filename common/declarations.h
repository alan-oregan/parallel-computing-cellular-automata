//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

// macros
#define INITIAL_INFECTION_ROW       0
#define INITIAL_EXPOSED_NUMBER      1

#define SIM_SIZE                    1000
#define GEN_LENGTH                  1000
#define OUTPUT_SAMPLE_SIZE          100

#define SUSCEPTIBLE                 'S'
#define EXPOSED                     'E'
#define INFECTED                    'I'
#define REMOVED                     'R'

#define BASE_CHANCE                 0.90
#define EXPOSED_INFECTION_CHANCE    0.00625
#define INFECTED_INFECTION_CHANCE   0.0125

#define EXPOSED_DURATION            7
#define INFECTED_DURATION           10
#define REMOVED_DURATION            90

#define NEIGHBOUR_COUNT             8

#define OUTPUT_FILE_DIR             "output"

// 0 - For no program output
// 1 - For showing the generation number as the program runs
#define GENERATION_OUTPUT           1

// 0 - no debug,
// 1 - check_neighbour debug,
// 2 - Initialize_world debug,
// 3 - output_to_file debug
#define DEBUG                       0

// parallel
#define THREAD_COUNT                8

// 4 - output at thread begin and end
// 5 - output when thread finishes a generation
// 6 - output when thread enters critical section
// 7 - output when thread is busy waiting
#define PARALLEL_DEBUG  	        4


// data structures
typedef struct cell {
    signed char status;
    signed char duration;
} CELL;

// Function prototypes
void initialize_world(CELL**, CELL**);
float check_neighbours(CELL**, int, int);
void output_to_file(CELL**, int, FILE*);
