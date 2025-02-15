# this is make file

CC = gcc
CFLAG = -c -WALL
Tree = ma

all:Tree

Tree: command.h listsort.o PrintTree.o Treecreation.o main.o
        $(CC) command.h listsort.o PrintTree.o Treecreation.o main.o -o ma
         

listsort.o: listsort.c
       $(CC) $(CFLAG) listsort.c	 

PrintTree.o: PrintTree.c
       $(CC) $(CFLAG) PrintTree.c	 

Treecreation.o: Treecreation.c
       $(CC) $(CFLAG) Treecreation.c	 	   

main.o: main.c
       $(CC) $(CFLAG) main.c	   

clean:
      rm -rf *o ma	   
