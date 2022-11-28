set title "SEIR Simulation Population";
set datafile separator ',';
set style function lines;
set key autotitle columnhead outside;
set grid;
plot "../population.csv" using 1:2 with linespoints, \
    "../population.csv" using 1:3 with linespoints, \
    "../population.csv" using 1:4 with linespoints, \
    "../population.csv" using 1:5 with linespoints;

print "Population graphed";
