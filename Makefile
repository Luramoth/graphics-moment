CC = gcc
CPP = g++
STRIP = strip
CFLAGS = -O2 -g -Wstrict-aliasing
CPPFLAGS = -std=gnu++20 $(CFLAGS)
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

SRCDIR = src
BUILDDIR = build
BIN = $(BUILDDIR)/graphics-moment

CPPFILES := $(shell find ./$(SRCDIR) -type f -name '*.cxx')
CFILES := $(shell find ./$(SRCDIR) -type f -name '*.c')
OBJ := $(CPPFILES:./$(SRCDIR)/%.cxx=$(BUILDDIR)/%.o)
OBJ += $(CFILES:./$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

.PHONY: all test clean

all: $(BIN)

test: $(BIN)
	@echo "[TEST] $@"
	@./$(BIN)

# Link rules for the final executable.
$(BIN): $(OBJ)
	@echo "[LD] $@"
	@$(CPP) $(LDFLAGS) $^ -o $@

# Compilation rules for *.cxx files.
$(BUILDDIR)/%.o: src/%.cxx
	@echo "[CPP] $< | $@"
	@mkdir -p $(shell dirname $@)
	@$(CPP) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: src/%.c
	@echo "[CC] $< | $@"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)