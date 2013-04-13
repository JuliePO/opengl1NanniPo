# Compilateur
CC = gcc
# $(BIN) est la nom du binaire genere
BIN = itd
BIN_PATH = bin
# FLAG
CFLAGS = -Wall -g
LDFLAGS= -lglut -lGL -lGLU -lm -lSDL
# INCLUDES
INC_PATH = -I include
# LIB
LIB_PATH = lib
# SRC
SRC_PATH = src
SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
# OBJET
OBJ_PATH = obj
OBJ = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

all: $(BIN)

$(BIN):$(OBJ)
	@echo "**** $@ ****"
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(BIN) $(OBJ) $(LDFLAGS)
	@echo "******* Compilation OK *******"


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "**** $@ ****"
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)
	@echo "Creation $@ OK"
	@echo "****************"

clean:
	rm -rf $(OBJ)
	@echo "File .o are all removed" 	

mrproper: clean
	rm -rf $(BIN_PATH)/$(BIN)
	@echo "File .o and .exe are all removed"
	
