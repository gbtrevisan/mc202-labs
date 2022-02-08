CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: calculadora

calculadora: calculadora.c
	gcc $(CFLAGS) -c numerosGigantes_funcoes.c $(LDFLAGS)
	gcc $(CFLAGS) -c calculadora.c $(LDFLAGS)
	gcc $(CFLAGS) calculadora.o numerosGigantes_funcoes.o $(LDFLAGS) -o calculadora

clean:
	rm -f calculadora
