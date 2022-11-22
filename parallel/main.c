#include "../common/declarations.h"

// TODO move to declarations
const int MAX_THREADS = 1024;

long thread_count;
long long n;
double sum;

int main() {
    int i;
    CELL *world[SIM_SIZE];
    CELL *newWorld[SIM_SIZE];

    FILE *population_file = fopen("population.csv", "w");

    srand((unsigned int)time(NULL));

    // add header to csv
    fprintf(population_file, "Generation,Population Susceptible,Population Exposed,Population Infected,Population Removed\n");

    // initialise world
    initialize_world(world, newWorld);

    // output generation 0
    output_to_file(world, 0, population_file);

    // insert threads

    // long       thread;  /* Use long in case of a 64-bit system */
    // pthread_t* thread_handles;

    // thread_handles = (pthread_t*) malloc(thread_count*sizeof(pthread_t));

    // for (thread = 0; thread < thread_count; thread++)
    //     pthread_create(&thread_handles[thread], NULL, thread_func, (void*)thread);

    // for (thread = 0; thread < thread_count; thread++)
    //     pthread_join(thread_handles[thread], NULL);

    // end of program

    printf("See /output and population.csv for output\n");

    // close files and free memory
    fclose(population_file);

    for (i = 0; i < SIM_SIZE; i++)
    {
        free(world[i]);
        free(newWorld[i]);
    }

    // free(thread_handles);

    return 0;
}
