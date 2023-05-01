//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "timer.h"

// starting row and number of initial infections for generation 0
#define INITIAL_INFECTION_ROW       0
#define INITIAL_EXPOSED_NUMBER      1

// the world size as SIM_SIZE * SIM_SIZE
#define SIM_SIZE                    1000

// Number of generations
#define GEN_LENGTH                  1000

// The output to file once in every {OUTPUT_SAMPLE_SIZE}
#define OUTPUT_SAMPLE_SIZE          100

#define SUSCEPTIBLE                 'S'
#define EXPOSED                     'E'
#define INFECTED                    'I'
#define REMOVED                     'R'

// probabilities of infection after neighbour interaction between 0 and 1
#define BASE_CHANCE                 0.40
#define EXPOSED_INFECTION_CHANCE    0.00625
#define INFECTED_INFECTION_CHANCE   0.0125

// duration of status before change (in # generations)
#define EXPOSED_DURATION            7
#define INFECTED_DURATION           14
#define REMOVED_DURATION            90

// number of neighbours using the Moore model
#define NEIGHBOUR_COUNT             8

#define OUTPUT_FILE_DIR             "output"

// 0 - For no program output
// 1 - For showing the generation number as the program runs
#define GENERATION_OUTPUT           1

// 0 - no debug
// 1 - check_neighbour debug,
// 2 - Initialize_world debug,
// 3 - output_to_file debug
#define DEBUG                       0

// number of threads for parallel program (needs to be a factor of SIM_SIZE)
#define THREAD_COUNT                8

// 0 - no debug
// 1 - output at thread begin and end
// 2 - output when thread finishes a generation
// 3 - output when thread enters critical section
// 4 - output when thread is busy waiting
#define PARALLEL_DEBUG              0

// 0 - Don't time the code
// 1 - Time the code
#define TIMER                       1

// data structures
typedef struct cell {
    signed char status;
    signed char duration;
} CELL;

// Function prototypes
void initialize_world(CELL**, CELL**);
float check_neighbours(CELL**, int, int);
void output_to_file(CELL**, int, FILE*);
