CC=gcc

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
	rm -R simulation_*
	rm -R *.o
	rm -R *.dat
	rm -R *.csv

clean-win:
	del /s /q simulation_*
	del /s /q *.o
	del /s /q *.dat
	del /s /q *.csv
