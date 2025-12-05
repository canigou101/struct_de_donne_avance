opt={-c}
main.exe: joueur.o sc_main.o
	gcc -o main.exe joueur.o sc_main.o

joueur.o : joueur.c 
	gcc -c joueur.c 

sc_main.o : sc_main.c
	gcc -c sc_main.c 


clean:
	rm *.o
cleanEXE: 
	rm *.exe