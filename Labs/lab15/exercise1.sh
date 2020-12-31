gcc -c main.c
gcc -c selection.c
ar -r libselsort selection.o
gcc -o main main.o libselsort
./main