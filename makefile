TARGET = libcollections

SRC = ./src
TEST = ./test
DIST = ./dist
SHARED = ./shared
INCLUDE = ./include

CC = gcc
LIBS = -lcollections
FLAGS = -I$(INCLUDE) -Wall -O3 -march=native

OBJECTS = $(patsubst $(SRC)/%.c,$(DIST)/%.o,$(wildcard $(SRC)/*.c))
TEST_BINS = $(patsubst $(TEST)/test_%.c,$(DIST)/%.test,$(wildcard $(TEST)/test_*.c))

ifeq ($(PREFIX),)
	PREFIX := /usr
endif

all: $(SHARED)/$(TARGET).so

.PHONY: clean install uninstall format test

$(DIST) $(SHARED):
	mkdir -p $@

$(DIST)/%.o: $(SRC)/%.c $(INCLUDE)/%.h | $(DIST)
	$(CC) -fPIC -c -o $@ $< $(FLAGS)

$(SHARED)/$(TARGET).so: $(OBJECTS) | $(SHARED)
	$(CC) -shared -o $@ $^ $(FLAGS)

$(DIST)/%.test: $(TEST)/test_%.c | $(DIST)
	$(CC) -o $@ $< $(LIBS) $(FLAGS)

test: $(TEST_BINS) | $(DIST)
	for f in $^; do ./$$f; done

clean:
	rm -rf $(DIST) $(SHARED)

install:
	mkdir -p $(PREFIX)/include/$(TARGET)
	cp $(INCLUDE)/*.h $(PREFIX)/include/$(TARGET)
	cp $(SHARED)/$(TARGET).so $(PREFIX)/lib/$(TARGET).so

uninstall:
	rm -rf $(PREFIX)/include/$(TARGET)
	rm -rf $(PREFIX)/lib/$(TARGET)
