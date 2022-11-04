# parallel-computing-cellular-automata

## Pseudocode

```c
// ---------- PROGRAM AIMS ----------

/* To create a two-dimensional model, based on the concept of Cellular Automata,
and then To write computer programs (based on that model) which simulate the spread of the SARSCoV-2 virus through a population. */

```c
// ---------- DEFINE MACROS ----------

#DEFINE SIM_SIZE        100
#DEFINE SIM_ITERATIONS  100

#DEFINE INITIAL_EXPOSED_ROW 4
#DEFINE INITIAL_EXPOSED     4

#DEFINE OUTPUT_SAMPLE_SIZE 10

// SEIR Model
#DEFINE SUSCEPTIBLE 0
#DEFINE INFECTED    1
#DEFINE REMOVED     2
#DEFINE EXPOSED     3

#DEFINE NEIGHBOUR_COUNT 8


// ---------- DEFINE GLOBALS ----------

world = INT[SIM_SIZE][SIM_SIZE];
newWorld = INT[SIM_SIZE][SIM_SIZE];
```

```c
// ---------- UTIL METHODS ----------

initialise_world(world*):
    INT exposed = 0
    FOR (INT row = 0; row < SIM_SIZE; row++):

        FOR (INT col = 0; col < SIM_SIZE; col++):

            IF (row == INITIAL_INFECTION_ROW && INITIAL_EXPOSED_NUMBER > exposed):
       world[row][col] = exposed
                exposed++

            ELSE:
       world[row][col] = SUSCEPTIBLE
    output_to_file(*world)


check_neighbours(world*, row, col):
    INT chance = 0
    NEIGHBOUR_COUNT = 8
    row_offset[8] = {0, 0, -1, 1, 1, 1, -1, -1}
    col_offset[8] = {-1, 1, 0, 0, -1, 1, -1, 1}

    FOR(INT i = 0; i < NEIGHBOUR_COUNT):
        neighbour = world[row + row_offset[i] % SIM_SIZE][col + col_offset[i] % SIM_SIZE]

        IF (neighbour == EXPOSED):
            chance += 0.0625

        ELSE IF (neighbour == INFECTED):
            chance += 0.125

    RETURN chance

output_to_file(newWorld*):
    *file = OPEN("output.txt", "w")

    FOR (INT row = 0; row < SIM_SIZE; row++):

        FOR (INT col = 0; col < SIM_SIZE - 1; col++):

            FPRINTF(*file, "%d, ", newWorld[row][col])

        FPRINTF(*file, "%d\n", newWorld[row][col])
```

```c
// ---------- MAIN METHOD ----------

initialise_world(*world)

FOR (INT ITERATION = 1; ITERATION <= SIM_ITERATIONS; ITERATION++):

    FOR (INT row = 0; row < SIM_SIZE; row++):

        FOR (INT col = 0; col < SIM_SIZE; col++):

            IF (world[row][col] == SUSCEPTIBLE)
                INT chance = check_neighbours(world*, row, col)

                IF (randfloat(0, 1) <= chance):
                    newWorld[row][col] = EXPOSED

            ELSE IF (world[row][col] == EXPOSED):
                newWorld[row][col] = INFECTED

            ELSE:
                newWorld[row][col] = REMOVED

    IF (ITERATION % OUTPUT_SAMPLE_SIZE == 0):
        output_to_file(*newWorld)

    world = newWorld

close_output_files();

RETURN 0
```

## Flowchart

![Flowchart of serial pseudocode](/serial/Flowchart.drawio.png)
