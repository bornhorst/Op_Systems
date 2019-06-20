
all: header timer piper signaler

header: header.o
	gcc -g -o header header.o

timer: timer.o
	gcc -g -o timer timer.o

piper: piper.o
	gcc -g -o piper piper.o

signaler: signaler.o
	gcc -g -o signaler signaler.o

header.o: header.c
	gcc -c -g -o header.o header.c

timer.o: timer.c
	gcc -c -g -o timer.o timer.c

piper.o:
	gcc -c -g -o piper.o piper.c

signaler.o:
	gcc -c -g -o signaler.o signaler.c
