# name of the binary
BIN = graphics-moment

# all the directories
SRCDIR = src/
BLDDIR = build/

# flags for g++
CFLAGS = -std=c++17 -O2

# libararies
LDFLAGS = 


$(BIN): $(SRCDIR)main.cxx
	g++ $(CFLAGS) -o $(BLDDIR)graphics-moment $(SRCDIR)main.cxx $(LDFLAGS)

.PHONY: test clean

test: $(BIN)
	./$(BLDDIR)$(BIN)

clean: 
	rm -f $(BLDDIR)$(BIN)