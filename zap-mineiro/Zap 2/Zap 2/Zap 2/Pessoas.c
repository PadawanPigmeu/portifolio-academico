#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pessoas.h"

#define VERDADEIRO (1 == 1)
#define FALSO (!VERDADEIRO)

void leDados_pessoas(dados_pessoas* pessoas){
	char nome[TAMANHO_MAXIMO_NOME];
	int id, i = 1, validador;
	FILE* cadastro;
	cadastro = fopen("cadastro.txt", "r");
	if (cadastro == NULL) {
		fprintf(stderr, "Uai, nao tem ninguem cadastrado!\n");
		return;
	} else {
		while ((fscanf(cadastro, "%d %d", &id, &validador) != EOF) && (fgets(nome, TAMANHO_MAXIMO_NOME, cadastro) != NULL)) {
			strcpy(pessoas[i].nome, nome);
			pessoas[i].id = id;
			pessoas[i].validador = validador;
			i++;
		}
	}
	fclose(cadastro);
}

void cadastra_Pessoas(dados_pessoas* pessoas, int nPessoas) {
	FILE* cadastro;
	FILE* nID;
	nID = fopen("nIDpessoa.txt", "w");
	cadastro = fopen("cadastro.txt", "a");

	if ((cadastro == NULL) || (nID == NULL)) {
		fprintf(stderr, "Falha ao abrir o arquivo.\n");
		return;
	}

	pessoas[nPessoas].id = nPessoas;
	pessoas[nPessoas].validador = VERDADEIRO;

	printf("ID: %d\n", nPessoas);
	printf("Digite o nome da pessoa: [30 Caracteres]:\n");
	getchar();
	fgets(pessoas[nPessoas].nome, TAMANHO_MAXIMO_NOME, stdin);
	
	fprintf(cadastro, "%d %d %s", pessoas[nPessoas].id, pessoas[nPessoas].validador, pessoas[nPessoas].nome);
	fprintf(nID, "%d", pessoas[nPessoas].id);

	printf("Cadastro concluido com sucesso, o trem bao.\n");

	fclose(nID);
	fclose(cadastro);
}

int descobre_ID(int nPessoas) {
	int id;
	FILE* nID;
	nID = fopen("nIDpessoa.txt", "r");
	if (nID == NULL) {
		return nPessoas;
	}
	fscanf(nID, "%d", &id);

	if (nPessoas <= id) {
		nPessoas = id;
		return nPessoas;
	}
	return nPessoas;
	fclose(nID);
}

void listarPorID(dados_pessoas* pessoas, int nPessoas) {
	int i, l, idInvalido = 0;
	FILE* cadastro;
	cadastro = fopen("cadastro.txt", "r");
	if (cadastro != NULL) {
		for (l = 1; l <= nPessoas; l++) {
			if (pessoas[l].validador == 0) {
				idInvalido++;
			}
		}
		if (idInvalido == nPessoas) {
			printf("Uai, tem ninguem cadastrado nao so.\n");
		}
		else {
			printf("ID | NOME\n");
			for (i = 1; i <= nPessoas; i++) {
				if (pessoas[i].validador == VERDADEIRO) {
					printf("%-2d | %-2s", pessoas[i].id, pessoas[i].nome);
				}
			}
			fclose(cadastro);
		}
	}
}

void listarPorNome(dados_pessoas* pessoas, int nPessoas) {
	int i, j, r, l, k, auxID, idInvalido = 0;
	char aux[TAMANHO_MAXIMO_NOME];
	FILE* cadastro;
	cadastro = fopen("cadastro.txt", "r");
	if (cadastro == NULL) {
		idInvalido = 1;
	}
	if (cadastro != NULL) {
		idInvalido = 0;
		for (k = 1; k <= nPessoas; k++) {
			if (pessoas[k].validador == 0) {
				idInvalido++;
			}
		}
	}
		if (idInvalido == nPessoas) {
			printf("Nao da pra listar o que nao foi cadastrado!\n");
		}
		else if (cadastro != NULL) {
			for (i = 1; i <= nPessoas; i++) {
				if (pessoas[i].validador == VERDADEIRO) {
					for (j = i + 1; j <= nPessoas; j++) {
						if (pessoas[j].validador == VERDADEIRO) {
							r = strcmp(pessoas[i].nome, pessoas[j].nome);
							if (r > 0) {
								strcpy(aux, pessoas[i].nome);
								strcpy(pessoas[i].nome, pessoas[j].nome);
								strcpy(pessoas[j].nome, aux);
								auxID = pessoas[i].id;
								pessoas[i].id = pessoas[j].id;
								pessoas[j].id = auxID;
							}
						}
					}
				}
			}
		printf("ID | NOME\n");
		for (l = 1; l <= nPessoas; l++) {
			if (pessoas[l].validador == VERDADEIRO) {
				printf("%-2d | %-2s", pessoas[l].id, pessoas[l].nome);
			}
		}
		fclose(cadastro);
	}
}

void invalidarPessoas(dados_pessoas* pessoas, int nPessoas) {
	FILE* cadastro;
	int invID, i;
	cadastro = fopen("cadastro.txt", "w");

	printf("Digite o ID da pessoa que quer invalidar (numerozinho do lado do nome):\n");
	scanf("%d", &invID);

	if ((invID <= nPessoas) && (pessoas[invID].validador == VERDADEIRO)) {
		for (i = 1; i <= nPessoas; i++) {
			if (invID == i) {
				fprintf(cadastro, "%d 0 %s", pessoas[invID].id, pessoas[invID].nome);
			}
			else {
				fprintf(cadastro, "%d %d %s", pessoas[i].id, pessoas[i].validador, pessoas[i].nome);
			}
		}
		printf("ID cancelado com sucesso.\n");
	}
	fclose(cadastro);
}

void menu_pessoas(void) {
	int operacao, nPessoas = 0;
	dados_pessoas* pessoas;
	pessoas = NULL;
	nPessoas = descobre_ID(nPessoas);
	do {
		pessoas = realloc(pessoas, (nPessoas + 1) * sizeof(dados_pessoas));
		printf("\nBota ai o que ce quer fazer\n");
		printf("1 - Cadastrar nova pessoa.\n"
			"2 - Listar em ordem crescente de ID.\n"
			"3 - Listar os nomes em ordem alfabetica.\n"
			"4 - Invalidar um cadastro.\n"
			"0 - Voltar.\n\n");
		scanf("%d", &operacao);
		switch (operacao) {
		case 0:
			return;
		case 1:
			nPessoas++;
			pessoas = realloc(pessoas, (nPessoas + 1) * sizeof(dados_pessoas));
			cadastra_Pessoas(pessoas, nPessoas);
			break;
		case 2:
			leDados_pessoas(pessoas);
			listarPorID(pessoas, nPessoas);
			break;
		case 3:
			leDados_pessoas(pessoas);
			listarPorNome(pessoas, nPessoas);
			break;
		case 4:
			leDados_pessoas(pessoas);
			invalidarPessoas(pessoas, nPessoas);
			break;
		default:
			printf("Esse numero ai nao pode meu fi\n");
			break;
		}
	} while (operacao != 0);
	free(pessoas);
}