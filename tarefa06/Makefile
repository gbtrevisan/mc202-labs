CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: sala_de_espera

sala_de_espera: sala_de_espera.c hospital.c
	gcc $(CFLAGS) -c sala_de_espera.c $(LDFLAGS)
	gcc $(CFLAGS) -c hospital.c $(LDFLAGS)
	gcc $(CFLAGS) sala_de_espera.o hospital.o $(LDFLAGS) -o sala_de_espera

clean:
	rm -f sala_de_espera
