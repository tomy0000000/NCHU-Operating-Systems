gcc -c -fPIC main.c
gcc -c -fPIC selection.c
gcc selection.o -shared -o libselsort.so
gcc -o main main.o libselsort.so
gcc -o main main.o ./libselsort.so
./main