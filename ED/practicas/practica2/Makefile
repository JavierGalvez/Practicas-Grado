INC = ./include
OBJ = ./obj
SRC = ./src
BIN = ./bin
DOC = ./doc
LIB = ./lib
CXX = g++
CPPFLAGS = #-Wall -g

all: $(BIN)/PruebaVector $(BIN)/PruebaFecha $(BIN)/PruebaCronologia

# ************ Generación de documentación ******************
documentacion:
	doxygen $(DOC)/doxys/Doxyfile

# ************ Binarios ************

$(BIN)/PruebaVector: $(SRC)/PruebaVector.cpp $(INC)/VectorDinamico.h $(INC)/VectorDinamico.cpp
	$(CXX) -I$(INC) $(SRC)/PruebaVector.cpp -o $@

$(BIN)/PruebaFecha: $(OBJ)/PruebaFecha.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaFecha.o  $(OBJ)/FechaHistorica.o -o $@

$(BIN)/PruebaCronologia: $(OBJ)/PruebaCronologia.o $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaCronologia.o  $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o -o $@

# ************ Compilación de módulos ************

$(OBJ)/PruebaFecha.o: $(SRC)/PruebaFecha.cpp $(INC)/FechaHistorica.h
	$(CXX) -c $(SRC)/PruebaFecha.cpp -I$(INC) -o $@

$(OBJ)/PruebaCronologia.o: $(SRC)/PruebaCronologia.cpp $(INC)/Cronologia.h
	$(CXX) -c $(SRC)/PruebaCronologia.cpp -I$(INC) -o $@

$(OBJ)/FechaHistorica.o: $(SRC)/FechaHistorica.cpp $(INC)/FechaHistorica.h $(INC)/VectorDinamico.h $(INC)/VectorDinamico.cpp
	$(CXX) -c $(SRC)/FechaHistorica.cpp -I$(INC) -o $@

$(OBJ)/Cronologia.o: $(SRC)/Cronologia.cpp $(INC)/Cronologia.h $(INC)/FechaHistorica.h
	$(CXX) -c $(SRC)/Cronologia.cpp -I$(INC) -o $@

# ************ Limpieza ************

clean:
	rm -f $(OBJ)/* $(BIN)/* $(LIB)/*
	rm -rf $(DOC)/doxygen_output

tgz: clean
	tar -zcvf cronologia.tgz ../practica2/
