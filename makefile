TARGET = libcollections.so

SRC = ./src
TEST = ./test
DIST = ./dist
SHARED = ./shared
INCLUDE = ./include

LIBS = 
FLAGS = -I$(INCLUDE)

OBJECTS = $(patsubst $(SRC)/%.c,$(DIST)/%.o,$(wildcard $(SRC)/*.c))

ifeq ($(PREFIX),)
	PREFIX := /usr
endif

.PHONY: clean

$(DIST) $(SHARED):
	mkdir -p $@

$(DIST)/%.o: $(SRC)/%.c | $(DIST)
	$(CC) -fPIC -c -o $@ $< $(FLAGS) $(LIBS)

$(SHARED)/$(TARGET): $(OBJECTS) | $(SHARED)
	$(CC) -shared -o $@ $^ $(FLAGS) $(LIBS);

clean:
	rm -rf $(DIST) $(SHARED)

install:
	install -Dm644 $(INCLUDE)/*.h $(PREFIX)/include/libcollections
	install -Dm755 $(DIST)/$(TARGET) $(PREFIX)/lib/libcollections

uninstall:
	rm -rf $(PREFIX)/include/libcollections
	rm -rf $(PREFIX)/lib/libcollections
