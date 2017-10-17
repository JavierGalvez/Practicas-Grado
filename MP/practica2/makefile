# Definición de macros para definir las carpetas de trabajo
BIN=./bin
OBJ=./obj
SRC=./src
INC=./include
LIB=./lib
ZIP=./zip
# Opciones de compilación
# -Wall muestra todas las advertencias
# -g compila en modo "depuración"
OPT=-Wall -g
# Nombre de la práctica
PRJ=practica2

# Las macros se usan en las reglas del makefile como si fuesen variables
# que se sustituyen por su valor definido anteriormente
all : $(BIN)/byte 

$(BIN)/byte: $(OBJ)/main.o $(LIB)/libbyte.a
	g++ $(OBJ)/main.o -L$(LIB) -lbyte -o $(BIN)/byte

$(LIB)/libbyte.a: $(OBJ)/byte.o
	ar rvs $(LIB)/libbyte.a $(OBJ)/byte.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/byte.h
	g++ -c $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/byte.o: $(SRC)/byte.cpp $(INC)/byte.h
	g++ -c $(SRC)/byte.cpp -o $(OBJ)/byte.o -I$(INC)

clean: 
	rm -f $(OBJ)/*.o $(BIN)/* $(LIB)/* $(ZIP)/*
	
zip: clean
	zip -r $(ZIP)/$(PRJ).zip *

