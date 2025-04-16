#Stephen Bangs
#Lab 1 Makefile - UNIX std I/O, Strings, and stat() 
#4/16/25
#Makes Caesar Cipher, XOR cipher, and mystat programs from caesar.c, xor.c, and mystat.c source files.
#Also cleans, and tars files using make clean and make tar commands

#adding line for test credential commit
DEBUG = -g3 -O0

CFLAGS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wextra -Werror -Wpedantic -Wno-return-local-addr -Wunsafe-loop-optimizations -Wuninitialized $(DEBUG)

CC = gcc

hex-2-float = hex-2-float
float-2-hex = float-2-hex

TARGETS = $(hex-2-float) $(float-2-hex)
CSRCS = $(hex-2-float).c $(float-2-hex).c
COBJS = $(hex-2-float).o $(float-2-hex).o

all: ${TARGETS}

.PHONY: clean tar

$(COBJS): $(CSRCS)
	$(CC) $(CFLAGS) -c $(@:.o=.c)

$(TARGETS): $(COBJS)
	$(CC) $(@).o -o $(@) -lm

clean:
	rm -f $(COBJS) $(TARGETS) *~

LAB = 03
TAR_FILE = stbangs_Lab$(LAB).tar.gz

tar:
	rm -f $(TAR_FILE)
	tar cvfa $(TAR_FILE) ?akefile *.[ch]
	tar tvaf $(TAR_FILE)
