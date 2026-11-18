#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pessoas.h"
#include "Grupos.h"

#define VERDADEIRO (1 == 1)
#define FALSO (!VERDADEIRO)

void leDados_grupos(dados_grupos* grupos) {
	char nome[TAMANHO_MAXIMO_NOME_GRUPO];
	int id, i = 1, validador;
	FILE* cadastro;
	cadastro = fopen("cadastroGrupo.txt", "r");
	if (cadastro == NULL) {
		fprintf(stderr, "Nenhum grupo aqui.\n");
		return;
	}
	else {
		while ((fscanf(cadastro, "%d %d", &id, &validador) != EOF) && (fgets(nome, TAMANHO_MAXIMO_NOME_GRUPO, cadastro) != NULL)) {
			strcpy(grupos[i].nome, nome);
			grupos[i].id = id;
			grupos[i].validador = validador;
			i++;
		}
	}
	fclose(cadastro);
}

void cadastra_Grupos(dados_grupos* grupos, int nGrupos) {
	FILE* cadastro;
	FILE* nID;

	nID = fopen("nIDgrupo.txt", "w");
	cadastro = fopen("cadastroGrupo.txt", "a");

	if ((cadastro == NULL) || (nID == NULL)) {
		fprintf(stderr, "Deu problema pra abrir esse trem... digo, o arquivo.\n");
		return;
	}

	grupos[nGrupos].id = nGrupos;
	grupos[nGrupos].validador = VERDADEIRO;

	printf("ID: %d\n", nGrupos);
	printf("Digite o nome do grupo: [50 Caracteres]:\n");
	getchar();
	fgets(grupos[nGrupos].nome, TAMANHO_MAXIMO_NOME_GRUPO, stdin);

	fprintf(cadastro, "%d %d %s", grupos[nGrupos].id, grupos[nGrupos].validador, grupos[nGrupos].nome);
	fprintf(nID, "%d", grupos[nGrupos].id);

	fclose(nID);
	fclose(cadastro);
}

int descobre_IDgrupos(dados_grupos* grupos, int nGrupos) {
	int id;
	FILE* nID;
	nID = fopen("nIDgrupo.txt", "r");
	if (nID == NULL) {
		return nGrupos;
	}
	fscanf(nID, "%d", &id);

	if (nGrupos <= id) {
		nGrupos = id;
		return nGrupos;
	}
	return nGrupos;
	fclose(nID);
}

void listarPorIDgrupos(dados_grupos* grupos, int nGrupos) {
	int i, l, idInvalido = 0;
	FILE* cadastro;
	cadastro = fopen("cadastroGrupo.txt", "r");
	if (cadastro != NULL) {
		for (l = 1; l <= nGrupos; l++) {
			if (grupos[l].validador == 0) {
				idInvalido++;
			}
		}
		if (idInvalido == nGrupos) {
			printf("Nao tem nenhum grupo cadastrado aqui uai.\n");
			return;
		}
		else {
			printf("ID | NOME\n");
			for (i = 1; i <= nGrupos; i++) {
				if (grupos[i].validador == VERDADEIRO) {
					printf("%-2d | %-2s", grupos[i].id, grupos[i].nome);
				}
			}
			fclose(cadastro);
		}
	}
}

void listarPorNomeGrupos(dados_grupos* grupos, int nGrupos) {
	int i, j, r, l, k, auxID, idInvalido = 0;
	char aux[TAMANHO_MAXIMO_NOME];
	FILE* cadastro;
	cadastro = fopen("cadastroGrupo.txt", "r");
	if (cadastro == NULL) {
		idInvalido = 1;
	}
	if (cadastro != NULL) {
		idInvalido = 0;
		for (k = 1; k <= nGrupos; k++) {
			if (grupos[k].validador == 0) {
				idInvalido++;
			}
		}
	}
	if (idInvalido == nGrupos) {
		printf("Num tem nenhum grupo aqui nao minha flor.\n");
		return;
	}
	else if (cadastro != NULL) {
		for (i = 1; i <= nGrupos; i++) {
			if (grupos[i].validador == VERDADEIRO) {
				for (j = i + 1; j <= nGrupos; j++) {
					if (grupos[j].validador == VERDADEIRO) {
						r = strcmp(grupos[i].nome, grupos[j].nome);
						if (r > 0) {
							strcpy(aux, grupos[i].nome);
							strcpy(grupos[i].nome, grupos[j].nome);
							strcpy(grupos[j].nome, aux);
							auxID = grupos[i].id;
							grupos[i].id = grupos[j].id;
							grupos[j].id = auxID;
						}
					}
				}
			}
		}
		printf("ID | NOME\n");
		for (l = 1; l <= nGrupos; l++) {
			if (grupos[l].validador == VERDADEIRO) {
				printf("%-2d | %-2s", grupos[l].id, grupos[l].nome);
			}
		}
		fclose(cadastro);
	}
}

void invalidarGrupos(dados_grupos* grupos, int nGrupos) {
	FILE* cadastro;
	int invID, i;

	printf("Digite o ID do grupo que quer invalidar (o numerozinho do lado do grupo):\n");
	scanf("%d", &invID);

	if (invID != 0) {
		if ((invID <= nGrupos) && (grupos[invID].validador == VERDADEIRO)) {
			cadastro = fopen("cadastroGrupo.txt", "w");
			for (i = 1; i <= nGrupos; i++) {
				if (invID == i) {
					fprintf(cadastro, "%d 0 %s", grupos[invID].id, grupos[invID].nome);
				}
				else {
					fprintf(cadastro, "%d %d %s", grupos[i].id, grupos[i].validador, grupos[i].nome);
				}
			}
			printf("Grupo removido com sucesso.\n");
		}
		else {
			cadastro = fopen("cadastroGrupo.txt", "r");
			printf("Irra, ce mandou esse trem pro lixo, seu grupo nao existe mais.\n");
		}
	}
	else {
		cadastro = fopen("cadastroGrupo.txt", "r");
	}
	fclose(cadastro);
}

void inserirPessoas(dados_grupos* grupos, dados_pessoas* pessoas, int nGrupos, int nPessoas) {
	FILE* grupo;
	int idGrupo, idPessoa;
	char nome[TAMANHO_MAXIMO_NOME_GRUPO];

	printf("Digite o ID do grupo:");
	scanf("%d", &idGrupo);

	if ((idGrupo <= nGrupos) && (grupos[idGrupo].validador == VERDADEIRO)) {

		strcpy(nome, grupos[idGrupo].nome);
		nome[strlen(nome) - 1] = '\0';
		strcat(nome, ".txt");

		grupo = fopen(nome, "a");

		if (grupo == NULL) {
			fprintf(stderr, "O trem, o coiso, o ARQUIVO nao abriu.\n");
			return;
		}

		printf("Digite 0 se quiser parar de adicionar.\n");

		do {
			printf("\nDigite o ID da pessoa:");
			scanf("%d", &idPessoa);

			if (idPessoa != 0) {
				if ((pessoas[idPessoa].validador == VERDADEIRO) && (idPessoa <= nPessoas)) {
					fprintf(grupo, "%d %d\n", pessoas[idPessoa].id, pessoas[idPessoa].validador);
					printf("Pessoa adicionada com sucesso.\n");
				}
				else {
					printf("ID nao ta disponivel.\n");
				}
			}
		} while (idPessoa != 0);
		fclose(grupo);
	}
	else {
		printf("ID de grupo indisponivel.\n");
	}
}

void removerPessoas(dados_grupos* grupos, dados_pessoas* pessoas, int nGrupos, int nPessoas) {
	FILE* grupo;
	int idGrupo, idPessoa, i, nLinhas, IDsPessoas[LIMITE_PESSOAS_GRUPO], PessoasValidador[LIMITE_PESSOAS_GRUPO], confere = 0;
	char nome[TAMANHO_MAXIMO_NOME_GRUPO];
	int removedor;

	printf("Digite o ID do grupo:");
	scanf("%d", &idGrupo);

	if ((idGrupo <= nGrupos) && (grupos[idGrupo].validador == VERDADEIRO)) {

		strcpy(nome, grupos[idGrupo].nome);
		nome[strlen(nome) - 1] = '\0';
		strcat(nome, ".txt");

		nLinhas = contaLinha(nome);

		removedor = leGrupos(nome, IDsPessoas, PessoasValidador);

		grupo = fopen(nome, "w");

		if (grupo == NULL) {
			fprintf(stderr, "Falha ao abrir o arquivo\n");
			return;
		}
		if (removedor == VERDADEIRO) {
			printf("Digite o ID da pessoa:");
			scanf("%d", &idPessoa);
			if (idPessoa != 0) {
				for (i = 1; i <= (nLinhas - 1); i++) {
					if (idPessoa == IDsPessoas[i] && idPessoa <= nPessoas && PessoasValidador[i] == VERDADEIRO) {
						fprintf(grupo, "%d 0\n", IDsPessoas[i]);
						printf("Pessoa removida com sucesso.\n");
						confere++;
					}
					else if (idPessoa != IDsPessoas[i] && idPessoa <= nPessoas && pessoas[i].validador == VERDADEIRO) {
						fprintf(grupo, "%d %d\n", IDsPessoas[i], PessoasValidador[i]);
					}
					else if (idPessoa == IDsPessoas[i] && idPessoa <= nPessoas && PessoasValidador[i] == FALSO) {
						fprintf(grupo, "%d 0\n", IDsPessoas[i]);
						printf("Num sei cade esse sujeito, mas nao ta nesse grupo nao so.\n");
						confere++;
					}
				}
			}
			if (confere == 0) {
				printf("Nao sei cade esse sujeito, mas num ta nesse grupo nao so.\n");
			}
		}
		else {
			printf("Uai, nao tem ninguem nesse grupo ainda.\n");
		}
		fclose(grupo);
	}
	else {
		printf("ID de grupo indisponivel\n");
	}
}

int leGrupos(char nome[TAMANHO_MAXIMO_NOME_GRUPO], int IDsPessoas[LIMITE_PESSOAS_GRUPO], int PessoasValidador[LIMITE_PESSOAS_GRUPO]) {
	FILE* grupo;
	int id, validador, i = 1, verifica = 0;
	grupo = fopen(nome, "r");
	if (grupo == NULL) {
		printf("Uai, nao tem ninguem nesse grupo ainda.\n");
		return FALSO;
	}
	while (!feof(grupo)) {
		fscanf(grupo, "%d %d", &id, &validador);
		IDsPessoas[i] = id;
		PessoasValidador[i] = validador;
		i++;
		if (validador == VERDADEIRO) {
			verifica++;
		}
	}
	if (verifica > 0) {
		fclose(grupo);
		return VERDADEIRO;
	}
	else {
		fclose(grupo);
		return FALSO;
	}
	fclose(grupo);
}

int contaLinha(char nome[TAMANHO_MAXIMO_NOME_GRUPO]) {
	FILE* grupo;
	int nLinhas = 0;
	char linha;

	grupo = fopen(nome, "r");

	if (grupo == NULL) {
		return nLinhas;
	}

	do {
		fscanf(grupo, "%c", &linha);
		if (linha == '\n') {
			nLinhas++;
		}
	} while (!feof(grupo));
	fclose(grupo);
	return (nLinhas);
}

void menu_grupos(void) {
	int operacao, nGrupos = 0, nPessoas = 0;
	dados_grupos* grupos;
	dados_pessoas* pessoas;
	pessoas = NULL;
	grupos = NULL;
	nGrupos = descobre_IDgrupos(grupos, nGrupos);
	nPessoas = descobre_ID(nPessoas);
	do {
		grupos = realloc(grupos, (nGrupos + 1) * sizeof(dados_grupos));
		pessoas = realloc(pessoas, (nPessoas + 1) * sizeof(dados_pessoas));
		printf("\nDigita o que ce quer fazer nesse trem de grupo so\n");
		printf("1 - Cadastrar novo grupo\n"
			"2 - Listar em ordem de ID\n"
			"3 - Listar em ordem de nome\n"
			"4 - Invalidar grupos\n"
			"5 - Inserir pessoas em um grupo\n"
			"6 - Remover pessoas do grupo\n"
			"0 - Voltar\n");
		scanf("%d", &operacao);
		switch (operacao) {
		case 1:
			nGrupos++;
			grupos = realloc(grupos, (nGrupos + 1) * sizeof(dados_grupos));
			cadastra_Grupos(grupos, nGrupos);
			break;
		case 2:
			leDados_grupos(grupos);
			listarPorIDgrupos(grupos, nGrupos);
			break;
		case 3:
			leDados_grupos(grupos);
			listarPorNomeGrupos(grupos, nGrupos);
			break;
		case 4:
			leDados_grupos(grupos);
			invalidarGrupos(grupos, nGrupos);
			break;
		case 5:
			leDados_pessoas(pessoas);
			leDados_grupos(grupos);
			inserirPessoas(grupos, pessoas, nGrupos, nPessoas);
			break;
		case 6:
			leDados_pessoas(pessoas);
			leDados_grupos(grupos);
			removerPessoas(grupos, pessoas, nGrupos, nPessoas);
			break;
		default:
			break;
		}
	} while (operacao != 0);
	free(pessoas);
	free(grupos);
}