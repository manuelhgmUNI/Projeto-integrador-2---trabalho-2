APP = simulador


SRC = asm_gerador.c decode.c funcoes.c main.c memoria.c registradores.c ula.c controle.c datapath.c

all:
	gcc $(SRC) -o $(APP)


clear:
	rm -f $(APP)


gdb:
	gcc $(SRC) -g -o $(APP)