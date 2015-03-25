CC=gcc
LDFLAGS=
CFLAGS=-c -Wall
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ghostcat

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
