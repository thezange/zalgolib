vpath %.c src tests
vpath %.h include
vpath %.o bin

CPPFLAGS += -Iinclude
IDIR = include
BDIR = bin
TESTDIR = tests

HDR_ORDERED = lnsearch.h bnsearch.h lnode.h llist.h rszarr.h prioq.h
HDRS = $(patsubst %, $(IDIR)/%, $(HDR_ORDERED))

BIN_SRC = $(wildcard src/*.c)
BINS = $(patsubst src/%.c,bin/%.o,$(BIN_SRC))

TEST_SRC = $(wildcard tests/*_test.c)
TESTS = $(patsubst tests/%.c,tests/%,$(TEST_SRC))

all: $(BINS) $(BDIR)/libzalgo.a tests

$(BDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(BDIR)/libzalgo.a: $(BINS)
	ar rs $@ $(BINS)

tests: $(BDIR)/libzalgo.a $(TESTS)

# obj dep wont exit until after first expansion phase
# get correct obj and src deps., and only use obj dep for compiling
# old method of linking:
# tests/%_test:  $$(BDIR)/$$*.o,$$(BINS)) %_test.c
# $(LINK.c) $@.c $(filter %.o,$^) $(LOADLIBES) $(LDLIBS) -o $@
.SECONDEXPANSION:
tests/%_test: $(BDIR)/libzalgo.a %_test.c
	$(LINK.c) $@.c $< $(LOADLIBES) $(LDLIBS) -o $@

header: $(HDRS)
	cat $(HDRS) > zalgolib.h
	./prepheader.py

.PHONY: clean
clean:
	rm -f $(BDIR)/*.o
	rm -f $(TESTDIR)/*_test

