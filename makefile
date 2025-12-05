opt={-c}
main.exe: joueur.o avl.o matchmaking.o sc_main.o
	gcc -o main.exe joueur.o avl.o matchmaking.o sc_main.o

joueur.o : joueur.c 
	gcc -c joueur.c 

avl.o : avl.c avl.h
	gcc -c avl.c avl.h

matchmaking.o : matchmaking.c matchmaking.h
	gcc -c matchmaking.c matchmaking.h

sc_main.o : sc_main.c
	gcc -c sc_main.c 

clean:
	rm *.o
cleanEXE: 
	rm *.exe