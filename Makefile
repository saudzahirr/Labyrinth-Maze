CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = labyrinth.out
SRC = labyrinth.c

CASES = case/case-1.txt case/case-2.txt case/case-3.txt case/case-4.txt case/case-5.txt case/case-6.txt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

test: $(TARGET)
	@for case in $(CASES); do \
		echo "Running $$case ..."; \
		./$(TARGET) $$case; \
		echo ""; \
	done

clean:
	rm -f $(TARGET)
