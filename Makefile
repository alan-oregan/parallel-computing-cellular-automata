CC=gcc

## make all programs and output directory if non existent
all: simulation_p simulation_s | output

## make output directory
output:
	mkdir output

## compile parallel program
simulation_p: common/initialize_world.o common/check_neighbours.o common/output_to_file.o parallel/main.c
	$(CC) -pthread $? -o $@

## compile serial program
simulation_s: common/initialize_world.o common/check_neighbours.o common/output_to_file.o serial/main.c
	$(CC) $? -o $@

# compile common files
common/initialize_world.o: common/initialize_world.c
	$(CC) -c $? -o $@

common/check_neighbours.o: common/check_neighbours.c
	$(CC) -c $? -o $@

common/output_to_file.o: common/output_to_file.c
	$(CC) -c $? -o $@

# clean for Linux
clean:
	rm -rfv simulation_*
	rm -rfv common/*.o
	rm -rfv output/*.dat
	rm -rfv *.csv
	rm -rfv *.class

# Clean for Windows
clean-win:
	del /s /q simulation_*
	del /s /q *.o
	del /s /q *.dat
	del /s /q *.csv
	del /s /q *.class
