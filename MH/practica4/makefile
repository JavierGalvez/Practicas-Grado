SRC = ./src
OBJ = ./obj
INC = ./include
src = $(wildcard $(SRC)/*.cpp)
obj = $(src:$(SRC)/%.cpp=$(OBJ)/%.o)

CC = g++
CPPFLAGS = -g -lm

bb-bc: $(obj)
	$(CC) -O3 -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -O3 -o $@ -c $< -I$(INC)

.PHONY: clean
clean:
	rm -f $(obj) bb-bc
