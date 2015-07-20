CC=gcc -Wall -o
OBJ=raycaster.o coordonnee.o camera.o mur.o carte.o util.o affichage.o
EXE=raycaster
main: ${OBJ}
	${CC} ${EXE} ${OBJ} main.c -lm -lSDL

%.o: %.c %.h
	gcc -Wall -c -o $@ $<

clean:
	rm -f *.o
	rm -f ${EXE}
