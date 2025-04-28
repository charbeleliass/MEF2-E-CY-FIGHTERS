all: exec

main.o: main.c
       gcc -c main.c -o main.o
menu.o: menu.c
       gcc -c menu.c -o menu.o
structure.o: structure.c
       gcc -c structure.c -o structure.o
combat.o: combat.c
       gcc -c combat.c -o combat.o
choix.o: choix.c
       gcc -c choix.c -o choix.o
exec: main.o menu.o combat.o choix.o
       gcc main.o menu.o combat.o choix.o -o exec  
