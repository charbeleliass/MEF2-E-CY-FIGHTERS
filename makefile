all: exec

main.o: main.c tri.h
       gcc -c main.c -o main.o
       
menu.o: menu.c tri.h
       gcc -c menu.c -o menu.o
       
structure.o: structure.c tri.h
       gcc -c structure.c -o structure.o
       
combat.o: combat.c tri.h
       gcc -c combat.c -o combat.o
       
choix.o: choix.c tri.h
       gcc -c choix.c -o choix.o
       
exec: main.o menu.o combat.o choix.o
       gcc main.o menu.o combat.o choix.o -o exec  
       
clean:
      rm -f *.o
      rm exec
