#================================================
CFLAGS = -Wall -Wextra -pedantic -O2
LIBS = -lm -lcurses
CC = gcc
#------------------------------------------------
BIN_DIR = bin
BUILD_DIR = build
INCLUDES_DIR = includes
SRC_DIR = src
#------------------------------------------------
SRC = $(wildcard $(SRC_DIR)/*.c) 
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
# src/main.c -> build/main.o
#------------------------------------------------
PROGRAM = play
#================================================
.DEFAULT_GOAL = build

build: setup $(PROGRAM)

# This will create the ./game in the project root folder
$(PROGRAM): $(OBJS)
	$(CC) -I $(INCLUDES_DIR) $(CFLAGS) -o $@ $^ $(LIBS)

# This will create the .o files in LA-Project/build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -I $(INCLUDES_DIR) $(CFLAGS) -o $@ $^


# Quando o target de uma função é só um target e não um ficheiro, utilizamos o .PHONY
.PHONY: setup
setup:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	@-rm -r $(BUILD_DIR)
	@-rm $(PROGRAM)

# O - antes do comando significa que se o comando falhar, ele é ignorado
# O @ antes do comando significa que quando o comando for acionado, irá omitir  todos comandos acionados

# $@ - Variável que está a ser chamada

# wildcard - Função das Makefile em que dá uma lista de um determinado .c ou .any
# patsubst - PatSubstring é substituir uma determinada lista de .c por .o ou .any por .any
