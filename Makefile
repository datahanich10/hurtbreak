CC      := gcc
CFLAGS  := -Wall -Wextra -Iinclude
SRC     := src/main.c src/memfs.c src/treegen.c
OUT     := sync_hurtbreak

.PHONY: all clean run

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)

