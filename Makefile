CC=gcc

simulation: output_to_file.o initialize_world.o check_neighbours.o main.c
	$(CC) $? -o $@
	mkdir output

initialize_world.o: initialize_world.c
	$(CC) -c $? -o $@

check_neighbours.o: check_neighbours.c
	$(CC) -c $? -o $@

output_to_file.o: output_to_file.c
	$(CC) -c $? -o $@

clean:
	rm simulation*
	rm *.o
	rm -R output
	rm *.csv