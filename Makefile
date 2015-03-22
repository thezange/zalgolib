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

all: $(BINS) archive tests

$(BDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

archive: $(BINS)
	ar rs libzalgo.a $(BINS)

tests: archive $(TESTS)

# obj dep wont exit until after first expansion phase
# get correct obj and src deps., and only use obj dep for compiling
# old method of linking:
# tests/%_test:  $$(BDIR)/$$*.o,$$(BINS)) %_test.c
# $(LINK.c) $@.c $(filter %.o,$^) $(LOADLIBES) $(LDLIBS) -o $@
.SECONDEXPANSION:
tests/%_test: archive %_test.c
	$(LINK.c) $@.c libzalgo.a $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(BDIR)/*.o
	rm -f $(TESTDIR)/*_test
