CC = clang
SRC = src/*.c
CFLAGS = -g -Wall -Wformat -Werror -o
BIN = bin/graph
IN = input/
OUT = output/
RES = result/
CASE = 4

all: clean graph run cmp

graph:
	$(CC) $(CFLAGS) $(BIN) $(SRC)

run:
	./$(BIN) < $(IN)$(CASE).in > $(RES)$(CASE).my.out

cmp:
	diff $(OUT)$(CASE).out $(RES)$(CASE).my.out

clean:
	rm -f $(BIN) $(RES)*
