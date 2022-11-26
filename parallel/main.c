#include "../common/declarations.h"

FILE *population_file;

CELL *world[SIM_SIZE];
CELL *newWorld[SIM_SIZE];

int thread_completion_counter;
pthread_mutex_t mutex;
pthread_cond_t condition;

void* thread_func(void* rank) {
    int threadRank = (int) rank;

    int totalThreadCells = SIM_SIZE / THREAD_COUNT;

    int startIndex = totalThreadCells * threadRank;
    int lastIndex = startIndex + totalThreadCells;

    float chance;
    int generation, row, col;
    int i;
    #if (PARALLEL_DEBUG > 3)
        printf("\nThread %d: Begin!\tProcessing Rows: %d - %d for %d generations\n", threadRank, startIndex, lastIndex, GEN_LENGTH);
    #endif
    for (generation = 1; generation < GEN_LENGTH; generation++) {

        for (row = startIndex; row < lastIndex; row++) {
            for (col = 0; col < SIM_SIZE; col++) {
                switch (world[row][col].status) {
                    case SUSCEPTIBLE:
                        chance = check_neighbours(world, row, col);

                        if ((float)rand()/(float)RAND_MAX < chance) {
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

        #if (PARALLEL_DEBUG > 4)
            printf("Thread %d: finished generation: %d, Counter: %d\n", threadRank, generation, thread_completion_counter);
        #endif

        pthread_mutex_lock(&mutex); // lock while checking if output possible
        thread_completion_counter++; // count the thread as finished

        #if (PARALLEL_DEBUG > 5)
            printf("Thread %d: inside critical section, Counter: %d\n", threadRank, thread_completion_counter);
        #endif

        // if this is the last thread to finish then output to file
        if (thread_completion_counter == THREAD_COUNT) {

            thread_completion_counter = 0; // reset counter
            pthread_cond_broadcast(&condition);

            // output to file every sample size generation
            if (generation % OUTPUT_SAMPLE_SIZE == 0) {
                output_to_file(newWorld, generation, population_file);
            }

            // update world with newWorld
            for(i = 0; i < SIM_SIZE; i++){
                memcpy(world[i], newWorld[i], SIM_SIZE*sizeof(CELL));
            }

            // output generation progress
            #if (GENERATION_OUTPUT == 1)
                printf("\rGeneration %d/%d, Thread: %d", generation, GEN_LENGTH-1, threadRank);
            #endif

        } else {
            #if (PARALLEL_DEBUG > 6)
                printf("Thread %d: Waiting for other threads to finish\n", threadRank);
            #endif

            // busy wait until all threads have completed and output occurs
            while (pthread_cond_wait(&condition, &mutex) != 0);
        }

        // unlock mutex as output has been completed
        pthread_mutex_unlock(&mutex);
    }
    #if (PARALLEL_DEBUG > 3)
        printf("\nThread %d: End!\tProcessed Rows: %d - %d for %d generations\n", threadRank, startIndex, lastIndex, GEN_LENGTH);
    #endif
}

int main() {

    // initialise global variables
    thread_completion_counter = 0;
    population_file = fopen("population.csv", "w");

    if (population_file == NULL) {
        printf("Error creating population.csv");
    }

    // initialise local variables
    int i;
    int thread;

    pthread_t* thread_handles = (pthread_t*) malloc(THREAD_COUNT*sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);

    srand((unsigned int)time(NULL));

    // add header to csv
    fprintf(population_file, "Generation,Population Susceptible,Population Exposed,Population Infected,Population Removed\n");

    // initialise world
    initialize_world(world, newWorld);

    #if (GENERATION_OUTPUT == 1)
        printf("\rGeneration %d/%d", 0, GEN_LENGTH-1);
    #endif

    // output generation 0
    output_to_file(world, 0, population_file);

    // create threads
    for (thread = 0; thread < THREAD_COUNT; thread++)
        pthread_create(&thread_handles[thread], NULL, thread_func, (void*)thread);

    // wait for all threads to finish
    for (thread = 0; thread < THREAD_COUNT; thread++)
        pthread_join(thread_handles[thread], NULL);

    // output final generation regardless of sample size
    output_to_file(newWorld, GEN_LENGTH, population_file);

    printf("\nSee /output directory and population.csv file for output\n");

    // close files and free memory
    fclose(population_file);

    free(thread_handles);
    pthread_mutex_destroy(&mutex);

    for (i = 0; i < SIM_SIZE; i++)
    {
        free(world[i]);
        free(newWorld[i]);
    }

    return 0;
}
