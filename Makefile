CC := $(CROSS_COMPILE)gcc
CFLAGS := -O2 -g -Wall -Wmissing-prototypes -Wmissing-declarations

TARGETS := test-optparse

OPTPARSE_SRCS := optparse.c

all: $(TARGETS)

test-optparse: test-optparse.o optparse.o
	$(CC) $(CFLAGS) -o $@ $+

test-optparse.o: test-optparse.c optparse.h

optparse.o: optparse.c optparse.h
