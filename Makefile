CC = gcc
CPP = g++
STRIP = strip
CPPFLAGS = -std=gnu++20 -O2 -g -Wstrict-aliasing
LDFLAGS = -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi

SRCDIR = src
BUILDDIR = build
BIN = $(BUILDDIR)/graphics-moment

CPPFILES := $(shell find ./$(SRCDIR) -type f -name '*.cxx')
CFILES := $(shell find ./$(SRCDIR) -type f -name '*.c')
OBJ := $(CPPFILES:./$(SRCDIR)/%.cxx=$(BUILDDIR)/%.o)
COBJ := $(CFILES:./$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all test clean

all: $(BIN)

test: $(BIN)
	@echo "[TEST] $@"
	@./$(BIN)

# Link rules for the final executable.
$(BIN): $(OBJ) $(COBJ)
	@echo "[LD] $@"
	@$(CPP) $(LDFLAGS) $^ -o $@

# Compilation rules for *.cxx files.
$(BUILDDIR)/%.o: src/%.cxx
	@echo "[CPP] $< | $@"
	@mkdir -p $(shell dirname $@)
	@$(CPP) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: src/%.c
	@echo "[C] $< | $@"
	@mkdir -p $(shell dirname $@)
	@$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
