CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro.c arvoreBuscaBinaria.c
	gcc $(CFLAGS) -c mensageiro.c $(LDFLAGS)
	gcc $(CFLAGS) -c arvoreBuscaBinaria.c $(LDFLAGS)
	gcc $(CFLAGS) mensageiro.o arvoreBuscaBinaria.o -o mensageiro $(LDFLAGS)

clean:
	rm -f mensageiro
