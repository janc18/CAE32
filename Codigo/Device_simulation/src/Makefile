
CC = gcc
CFLAGS = 
SRC_DIR = .
OBJ_DIR = ../obj
BIN_DIR = ../executables

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SOURCES))

.PHONY: all clean $(OBJ_DIR) $(BIN_DIR)

all: $(EXECUTABLES)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%: $(OBJ_DIR)/%.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLES)

