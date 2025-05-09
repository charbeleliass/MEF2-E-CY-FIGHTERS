all: exec

main.o: main.c menu.h structure.h combat.h
	gcc -c main.c -o main.o
       
menu.o: menu.c structure.h choix.h combat.h
	gcc -c menu.c -o menu.o
       
structure.o: structure.c 
	gcc -c structure.c -o structure.o
       
combat.o: combat.c structure.h choix.h menu.h
	gcc -c combat.c -o combat.o
       
choix.o: choix.c structure.h
	gcc -c choix.c -o choix.o
       
exec: main.o menu.o combat.o choix.o structure.o
	gcc main.o menu.o combat.o choix.o structure.o -o exec  
       
clean:
	rm -f *.o
	rm -f exec
