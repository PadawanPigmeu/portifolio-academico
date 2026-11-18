#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pessoas.h"
#include "Grupos.h"
#include "Conversas.h"

int main(int argc, char** argv) {
	int operacao;
	do {
		printf("O que ce quer ver o coisinha bunita?\n");
		printf("1 - Menu das Pessoas\n"
			   "2 - Menu dos Grupos\n"
			   "3 - Menu de Conversas\n"
			   "0 - Fechar Programa\n");
		scanf("%d", &operacao);
		switch (operacao) {
		case 1:
			menu_pessoas();
			break;
		case 2:
			menu_grupos();
			break;
		case 3:
			menu_conversas();
			break;	
		default:
			printf("Esse numero ai nao pode meu fi.\n");
			break;
		}
	} while (operacao != 0);
}