vpath %.c src tests
vpath %.h include
vpath %.o bin

CPPFLAGS += -Iinclude
BDIR = bin
TESTDIR = tests

BIN_SRC = $(wildcard src/*.c)
BINS = $(patsubst src/%.c,bin/%.o,$(BIN_SRC))

TEST_SRC = $(wildcard tests/*_test.c)
TESTS = $(patsubst tests/%.c,tests/%,$(TEST_SRC))

all: $(BINS) tests

$(BDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

tests: $(BINS) $(TESTS)

.SECONDEXPANSION:
tests/%_test: $$(filter $$(BDIR)/$$*.o,$$(BINS))
	$(LINK.c) $@.c $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(BDIR)/*.o
	rm -f $(TESTDIR)/*_test
