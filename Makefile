# Makefile
# Usage:
# make          # Compile all binaries
# make clean    # Remove all binaries and objects


all: src/main

src/main: src/main.o
	gcc $? -o $@ -lcurl

src/main.o: src/main.c src/main.h
	gcc -c src/main.c -o $@

install: src/main
	@echo "The install target has not been completed"

clean:
	@rm -rvf src/main src/main.o
