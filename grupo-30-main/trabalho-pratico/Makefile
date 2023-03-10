FLAGS= -std=c99 -Wall -g -o1 -D_GNU_SOURCE 
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER=gcc
LIBS=libs
INCLUDES=include
SRC=src
OBJ=obj

all: programa-principal directories programa-testes

directories:
	mkdir Resultados Testes

programa-principal: $(wildcard $(SRC)/*.c)
	$(COMPILER) $(FLAGS) $(filter-out src/teste.c ,$(wildcard $(SRC)/*.c)) $(PKG)  -o programa-principal

programa-testes: $(filter-out src/main.c ,$(wildcard $(SRC)/*.c))
	$(COMPILER) $(FLAGS) $(filter-out src/main.c ,$(wildcard $(SRC)/*.c)) $(PKG)  -o programa-testes

clean: 
	rm programa-principal Resultados/*.txt

run: 
	./programa-principal
