#Stephen Bangs
#Lab 1 Makefile - UNIX std I/O, Strings, and stat() 
#4/16/25
#Makes Caesar Cipher, XOR cipher, and mystat programs from caesar.c, xor.c, and mystat.c source files.
#Also cleans, and tars files using make clean and make tar commands.
#added a git lazy command for source control, though I mostly still commit manually.

DEBUG = -g3 -O0

CFLAGS = -Wall -Wextra -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wunsafe-loop-optimizations -Wuninitialized -Werror

CC = gcc

caesar = caesar
xor = xor
mystat = mystat

TARGETS = $(caesar) $(xor) $(mystat) 
CSRCS = $(caesar).c $(xor).c $(mystat).c
COBJS = $(caesar).o $(xor).o $(mystat).o

all: ${TARGETS}

.PHONY: clean tar

$(COBJS): $(CSRCS)
	$(CC) $(CFLAGS) -c $(@:.o=.c)

$(TARGETS): $(COBJS)
	$(CC) $(@).o -o $(@)

clean:
	rm -f $(COBJS) $(TARGETS) *~ *.txt

LAB = 01
TAR_FILE = stbangs_Lab$(LAB).tar.gz

tar:
	rm -f $(TAR_FILE)
	tar cvfa $(TAR_FILE) ?akefile *.[ch]
	tar tvaf $(TAR_FILE)

git lazy:
	git add *.[ch] ?akefile
	git commit -m "lazy make git commit"
