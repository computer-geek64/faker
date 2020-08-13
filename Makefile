# Makefile
# Usage:
# make          # Compile all binaries
# make clean    # Remove all binaries and objects


all: src/faker

src/faker: src/main.o
	gcc $? -o $@ -lcurl

src/main.o: src/main.c src/main.h src/curl_helper.c src/curl_helper.h
	gcc -c src/main.c -o $@

clean:
	@rm -rvf src/faker src/main.o

install: src/faker
	install src/faker /usr/bin/faker

uninstall: /usr/bin/faker
	@rm -rvf $?
