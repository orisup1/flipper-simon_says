CC = gcc
CFLAGS = -Wall -I./src/game -I./src/utils
SRC = src/main.c src/game/game_logic.c src/game/input.c src/utils/random.c
OBJ = $(SRC:.c=.o)
TARGET = flipper_zero_game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)