#Nastase Maria
#311 CA

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=star_dust

build: $(TARGETS)

star_dust: star_dust.c
	$(CC) $(CFLAGS) star_dust.c -o star_dust

pack:
	zip -FSr 311CA_NastaseMaria_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
