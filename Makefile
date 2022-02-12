# inspiré de https://stackoverflow.com/questions/1484817/how-do-i-make-a-simple-makefile-for-gcc-on-linux

# make clean : supprimes les fichiers construits
# make : crée le programme
# make run : lance le programme  


LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra

BIN = bin/
SRC = src/
OBJ = obj/
INCLUDE = include/

SOURCES = $(wildcard $(SRC)*.c)
OBJETS = $(subst src/,,$(SOURCES:.c=.o))

EXEC = prog
EXEC_FILE = $(BIN)$(EXEC)

$(EXEC): $(OBJETS)

	$(CC) $(CFLAGS) -o $(BIN)$@ $^
	mv *.o $(OBJ)

$(OBJ)%.o: %.c %.h
	$(CCOBJ)

$(OBJ)main.o: main.c liste_freq.h liste_mots.h dict_contexte.h
	$(CCOBJ)


vpath %.h include/
vpath %.c src/


.PHONY:
run:
	$(EXEC_FILE)

clean:
	rm $(OBJ)*.o $(EXEC_FILE) -rf

