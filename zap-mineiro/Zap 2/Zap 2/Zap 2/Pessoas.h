#pragma once

#ifndef __PESSOAS_h__
#define __PESSOAS_h__

#define TAMANHO_MAXIMO_NOME 30 + 1

typedef unsigned char bool_t;

typedef struct cadastrar_pessoas {
	int id;
	char nome[TAMANHO_MAXIMO_NOME];
	bool_t validador;
}dados_pessoas;

void leDados_pessoas(dados_pessoas* pessoas);
void cadastra_Pessoas(dados_pessoas* pessoas, int nPessoas);
int descobre_ID(int nPessoas);
void listarPorID(dados_pessoas* pessoas, int nPessoas);
void listarPorNome(dados_pessoas* pessoas, int nPessoas);
void invalidarPessoas(dados_pessoas* pessoas, int nPessoas);
void menu_pessoas(void);

#endif