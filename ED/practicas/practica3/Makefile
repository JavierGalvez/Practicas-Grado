INC = ./include
OBJ = ./obj
SRC = ./src
BIN = ./bin
DOC = ./doc
LIB = ./lib
CXX = g++
CPPFLAGS = #-Wall -g

all: $(BIN)/pruebaPila $(BIN)/pruebaCola $(BIN)/pruebaVector

# ************ Generación de documentación ******************
documentacion:
	doxygen $(DOC)/doxys/Doxyfile

# ************ Binarios ************

$(BIN)/pruebaPila: $(SRC)/pruebaPila.cpp $(INC)/PilaMax.h $(INC)/PilaMaxVD.h $(SRC)/PilaMaxVD.cpp $(INC)/PilaMaxCola.h $(SRC)/PilaMaxCola.cpp $(INC)/VectorDinamico.h $(SRC)/VectorDinamico.cpp
	$(CXX) -I$(INC) $(SRC)/pruebaPila.cpp -o $@

$(BIN)/pruebaCola: $(SRC)/pruebaCola.cpp $(INC)/Cola.h $(SRC)/Cola.cpp
	$(CXX) -I$(INC) $(SRC)/pruebaCola.cpp -o $@

$(BIN)/pruebaVector: $(SRC)/pruebaVector.cpp $(INC)/VectorDinamico.h $(SRC)/VectorDinamico.cpp
	$(CXX) -I$(INC) $(SRC)/pruebaVector.cpp -o $@

# ************ Limpieza ************

clean:
	rm -f $(OBJ)/* $(BIN)/* $(LIB)/*
	rm -rf $(DOC)/doxygen_output

tgz: clean
	tar -zcvf cronologia.tgz ../practica2/
