CC=gcc

all: simulation_p simulation_s | output

output:
	mkdir output

simulation_p: common/initialize_world.o common/check_neighbours.o common/output_to_file.o parallel/main.c
	$(CC) -pthread $? -o $@

simulation_s: common/initialize_world.o common/check_neighbours.o common/output_to_file.o serial/main.c
	$(CC) $? -o $@

common/initialize_world.o: common/initialize_world.c
	$(CC) -c $? -o $@

common/check_neighbours.o: common/check_neighbours.c
	$(CC) -c $? -o $@

common/output_to_file.o: common/output_to_file.c
	$(CC) -c $? -o $@

clean:
	rm -rfv simulation_*
	rm -rfv common/*.o
	rm -rfv output/*.dat
	rm -rfv *.csv
	rm -rfv *.class

clean-win:
	del /s /q simulation_*
	del /s /q *.o
	del /s /q *.dat
	del /s /q *.csv
	del /s /q *.class
