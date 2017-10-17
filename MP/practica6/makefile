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
PRJ=practica6

# Las macros se usan en las reglas del makefile como si fuesen variables
# que se sustituyen por su valor definido anteriormente
all: $(BIN)/testarteASCII $(BIN)/testplano $(BIN)/testimagen $(BIN)/testMorphing

#==============
#   BINARIOS
#==============

$(BIN)/testarteASCII: $(OBJ)/testarteASCII.o $(LIB)/libimagen.a
	g++ $(OBJ)/testarteASCII.o -L$(LIB) -limagen -o $@

$(BIN)/testplano: $(OBJ)/testplano.o $(LIB)/libimagen.a
	g++ $(OBJ)/testplano.o -L$(LIB) -limagen -o $@

$(BIN)/testimagen: $(OBJ)/testimagen.o $(LIB)/libimagen.a
	g++ $(OBJ)/testimagen.o -L$(LIB) -limagen -o $@
	
$(BIN)/testMorphing: $(OBJ)/testMorphing.o $(LIB)/libimagen.a
	g++ $(OBJ)/testMorphing.o -L$(LIB) -limagen -o $@


#===============
#  BIBLIOTECAS
#===============

$(LIB)/libimagen.a: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/celda.o $(OBJ)/lista.o
	ar rvs $@ $^

#===============
#    OBJETOS
#===============

$(OBJ)/testarteASCII.o: $(SRC)/testarteASCII.cpp $(INC)/imagen.h $(INC)/byte.h
	g++ $(OPT) -c $(SRC)/testarteASCII.cpp -I$(INC) -o $@

$(OBJ)/testplano.o: $(SRC)/testplano.cpp $(INC)/imagen.h $(INC)/byte.h
	g++ $(OPT) -c $(SRC)/testplano.cpp -I$(INC) -o $@

$(OBJ)/testimagen.o: $(SRC)/testimagen.cpp $(INC)/imagen.h $(INC)/byte.h
	g++ $(OPT) -c $(SRC)/testimagen.cpp -I$(INC) -o $@

$(OBJ)/imagen.o: $(SRC)/imagen.cpp $(INC)/imagen.h $(INC)/pgm.h $(INC)/byte.h
	g++ $(OPT) -c $(SRC)/imagen.cpp -I$(INC) -o $@

$(OBJ)/byte.o: $(SRC)/byte.cpp $(INC)/byte.h
	g++ $(OPT) -c $(SRC)/byte.cpp -I$(INC) -o $@

$(OBJ)/pgm.o: $(SRC)/pgm.cpp $(INC)/pgm.h
	g++ $(OPT) -c $(SRC)/pgm.cpp -I$(INC) -o $@

$(OBJ)/lista.o: $(SRC)/lista.cpp $(INC)/lista.h
	g++ $(OPT) -c $(SRC)/lista.cpp -I$(INC) -o $@

$(OBJ)/celda.o: $(SRC)/celda.cpp $(INC)/lista.h
	g++ $(OPT) -c $(SRC)/celda.cpp -I$(INC) -o $@

$(OBJ)/testMorphing.o: $(SRC)/testMorphing.cpp $(INC)/lista.h
	g++ $(OPT) -c $(SRC)/testMorphing.cpp -I$(INC) -o $@

#==============
#    OTROS
#==============

clean:
	rm -f $(OBJ)/*.o $(BIN)/* $(LIB)/* $(ZIP)/*
zip: clean
	zip -r $(ZIP)/$(PRJ).zip *
