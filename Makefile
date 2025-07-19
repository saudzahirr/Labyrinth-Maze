CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = labyrinth.out
SRC = labyrinth.c

CASES = 1 2 3 4 5 6 7

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

test: $(TARGET)
	@for case in $(CASES); do \
		echo "Running $$case ..."; \
		./$(TARGET) case/case-$$case.txt; \
		echo ""; \
	done

clean:
	rm -f $(TARGET)
