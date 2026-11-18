#pragma once

#ifndef __GRUPOS_h__
#define __GRUPOS_h__

#define TAMANHO_MAXIMO_NOME_GRUPO 50 + 1
#define LIMITE_PESSOAS_GRUPO 256

typedef unsigned char bool_t;

typedef struct cadastrar_grupo {
	int id;
	char nome[TAMANHO_MAXIMO_NOME];
	bool_t validador;
}dados_grupos;

void leDados_grupos(dados_grupos* grupos);
void cadastra_Grupos(dados_grupos* grupos, int nGrupos);
int descobre_IDgrupos(dados_grupos* grupos, int nGrupos);
void listarPorIDgrupos(dados_grupos* grupos, int nGrupos);
void listarPorNomeGrupos(dados_grupos* grupos, int nGrupos);
void invalidarGrupos(dados_grupos* grupos, int nGrupos);
void inserirPessoas(dados_grupos* grupos, dados_pessoas* pessoas, int nGrupos, int nPessoas);
void removerPessoas(dados_grupos* grupos, dados_pessoas* pessoas, int nGrupos, int nPessoas);
int leGrupos(char nome[TAMANHO_MAXIMO_NOME_GRUPO], int IDsPessoas[LIMITE_PESSOAS_GRUPO], int PessoasValidador[LIMITE_PESSOAS_GRUPO]);
int contaLinha(char nome[TAMANHO_MAXIMO_NOME_GRUPO]);
void menu_grupos(void);

#endif