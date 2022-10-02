TARGET = libcollections.so

SRC = ./src
TEST = ./test
DIST = ./dist
SHARED = ./shared
INCLUDE = ./include

CC = gcc
LIBS =
FLAGS = -I$(INCLUDE)

OBJECTS = $(patsubst $(SRC)/%.c,$(DIST)/%.o,$(wildcard $(SRC)/*.c))
TEST_BINS = $(patsubst $(TEST)/test_%.c,$(DIST)/%.test,$(wildcard $(TEST)/test_*.c))

ifeq ($(PREFIX),)
	PREFIX := /usr
endif

all: $(SHARED)/$(TARGET)

.PHONY: clean install uninstall

$(DIST) $(SHARED):
	mkdir -p $@

$(DIST)/%.o: $(SRC)/%.c | $(DIST)
	$(CC) -fPIC -c -o $@ $< $(FLAGS) $(LIBS)

$(SHARED)/$(TARGET): $(OBJECTS) | $(SHARED)
	$(CC) -shared -o $@ $^ $(FLAGS) $(LIBS)

$(DIST)/%.test: $(TEST)/test_%.c $(TEST)/unit_test.h | $(DIST)
	@$(CC) -o $@ $< -lcollections

test: $(TEST_BINS) | $(DIST)
	@for f in $^; do ./$$f; done

clean:
	rm -rf $(DIST) $(SHARED)

install:
	mkdir -p $(PREFIX)/include/libcollections
	cp $(INCLUDE)/*.h $(PREFIX)/include/libcollections/
	cp $(SHARED)/$(TARGET) $(PREFIX)/lib/$(TARGET)

uninstall:
	rm -rf $(PREFIX)/include/libcollections
	rm -rf $(PREFIX)/lib/libcollections
