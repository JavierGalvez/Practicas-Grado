INC = ./include
OBJ = ./obj
SRC = ./src
BIN = ./bin
DOC = ./doc
LIB = ./lib
CXX = g++
CPPFLAGS = #-Wall -g

all: $(BIN)/PruebaFecha $(BIN)/PruebaIntervalo $(BIN)/PruebaEstadistica $(BIN)/PruebaUnion $(BIN)/PruebaCronologia $(BIN)/PruebaFiltrado

# ************ Generación de documentación ******************
documentacion:
	doxygen $(DOC)/doxys/Doxyfile

# ************ Binarios ************

$(BIN)/PruebaFecha: $(OBJ)/PruebaFecha.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaFecha.o  $(OBJ)/FechaHistorica.o -o $@

$(BIN)/PruebaIntervalo: $(OBJ)/PruebaIntervalo.o $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaIntervalo.o  $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o -o $@

$(BIN)/PruebaUnion: $(OBJ)/PruebaUnion.o $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaUnion.o  $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o -o $@

$(BIN)/PruebaEstadistica: $(OBJ)/PruebaEstadistica.o $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaEstadistica.o  $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o -o $@

$(BIN)/PruebaFiltrado: $(OBJ)/PruebaFiltrado.o $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaFiltrado.o  $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o -o $@

$(BIN)/PruebaCronologia: $(OBJ)/PruebaCronologia.o $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o
	$(CXX) -I$(INC) $(OBJ)/PruebaCronologia.o  $(OBJ)/Cronologia.o $(OBJ)/FechaHistorica.o -o $@


# ************ Compilación de módulos ************

$(OBJ)/PruebaFecha.o: $(SRC)/PruebaFecha.cpp $(INC)/FechaHistorica.h
	$(CXX) -c $(SRC)/PruebaFecha.cpp -I$(INC) -o $@

$(OBJ)/PruebaUnion.o: $(SRC)/PruebaUnion.cpp $(INC)/Cronologia.h
	$(CXX) -c $(SRC)/PruebaUnion.cpp -I$(INC) -o $@

$(OBJ)/PruebaIntervalo.o: $(SRC)/PruebaIntervalo.cpp $(INC)/Cronologia.h
	$(CXX) -c $(SRC)/PruebaIntervalo.cpp -I$(INC) -o $@

$(OBJ)/PruebaEstadistica.o: $(SRC)/PruebaEstadistica.cpp $(INC)/Cronologia.h
	$(CXX) -c $(SRC)/PruebaEstadistica.cpp -I$(INC) -o $@

$(OBJ)/PruebaFiltrado.o: $(SRC)/PruebaFiltrado.cpp $(INC)/Cronologia.h
	$(CXX) -c $(SRC)/PruebaFiltrado.cpp -I$(INC) -o $@

$(OBJ)/PruebaCronologia.o: $(SRC)/PruebaCronologia.cpp $(INC)/Cronologia.h
	$(CXX) -c $(SRC)/PruebaCronologia.cpp -I$(INC) -o $@

$(OBJ)/FechaHistorica.o: $(SRC)/FechaHistorica.cpp $(INC)/FechaHistorica.h
	$(CXX) -c $(SRC)/FechaHistorica.cpp -I$(INC) -o $@

$(OBJ)/Cronologia.o: $(SRC)/Cronologia.cpp $(INC)/Cronologia.h $(INC)/FechaHistorica.h
	$(CXX) -c $(SRC)/Cronologia.cpp -I$(INC) -o $@

# ************ Limpieza ************

clean:
	rm -f $(OBJ)/* $(BIN)/* $(LIB)/*
	rm -rf $(DOC)/doxygen_output
	find ./datos -type f ! -name 'timeline_*' -delete

tgz: clean
	tar -zcvf cronologia.tgz ../practica4/
