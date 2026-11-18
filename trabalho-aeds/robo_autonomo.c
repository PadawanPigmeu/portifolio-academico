#include <stdio.h>
#include <stdlib.h>

/* ========================================================================= */
/* ESTRUTURAS DO ZIVIANI                                  */
/* ========================================================================= */
typedef struct {
    int tipo;
    int quantidade;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct {
    TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista) {
    Lista->Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista) {
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista) {
    Lista->Ultimo->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item) {
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL) return;
    q = p->Prox;
    *Item = q->Item;
    p->Prox = q->Prox;
    if (p->Prox == NULL) Lista->Ultimo = p;
    free(q);
}

/* ========================================================================= */
/* 1. MAPEAMENTO DE CORES EXPANDIDO                                          */
/* ========================================================================= */
int mapearCor(int valor) {
    if (valor == 0) return 1;    // Preto (Fundo/Asfalto)
    if (valor == 128) return 2;  // Vermelho
    if (valor == 255) return 3;  // Branco
    if (valor == 100) return 4;  // Exemplo: Amarelo
    if (valor == 50) return 5;   // Exemplo: Azul
    
    return -1; // Ruído
}

/* ========================================================================= */
/* 2. DFA GENÉRICA PARA QUALQUER PLACA DE TRÂNSITO                           */
/* Em vez de fixar o 2 e 3, ela recebe cor_borda e cor_meio como variáveis.  */
/* ========================================================================= */
int verificaPlacaDFA(TipoLista lista, int cor_borda, int cor_meio) {
    TipoApontador Aux = lista.Primeiro->Prox;
    int estado = 0;

    while (Aux != NULL) {
        int tipo = Aux->Item.tipo;

        switch (estado) {
            case 0: // Aguarda o Preto (Fundo = 1)
                if (tipo == 1) estado = 1;
                break;
            case 1: // Aguarda a Borda da placa
                if (tipo == cor_borda) estado = 2;
                else if (tipo == 1) estado = 1;
                else estado = 0;
                break;
            case 2: // Aguarda o Meio da placa (letra ou desenho)
                if (tipo == cor_meio) estado = 3;
                else if (tipo == 1) estado = 1;
                else estado = 0;
                break;
            case 3: // Aguarda a Borda do outro lado
                if (tipo == cor_borda) estado = 4;
                else if (tipo == 1) estado = 1;
                else estado = 0;
                break;
            case 4: // Aguarda o Preto pra confirmar que saiu da placa
                if (tipo == 1) return 1; // ACHOU A PLACA!
                else estado = 0;
                break;
        }
        Aux = Aux->Prox;
    }
    return 0;
}

/* ========================================================================= */
/* 3. DFA PARA FAIXA DE PEDESTRES                                            */
/* A faixa é uma repetição de Preto(1) e Branco(3). O autômato exige que     */
/* ele veja pelo menos 3 listras brancas separadas por asfalto preto.        */
/* ========================================================================= */
int verificaFaixaPedestreDFA(TipoLista lista) {
    TipoApontador Aux = lista.Primeiro->Prox;
    int estado = 0;

    while (Aux != NULL) {
        int tipo = Aux->Item.tipo;

        switch (estado) {
            case 0: // Aguarda Preto (asfalto antes da faixa)
                if (tipo == 1) estado = 1;
                break;
            case 1: // Leu asfalto(1). Aguarda 1ª listra Branca (3)
                if (tipo == 3) estado = 2;
                else if (tipo == 1) estado = 1;
                else estado = 0;
                break;
            case 2: // Aguarda asfalto entre as listras (1)
                if (tipo == 1) estado = 3;
                else estado = 0;
                break;
            case 3: // Aguarda 2ª listra Branca (3)
                if (tipo == 3) estado = 4;
                else if (tipo == 1) estado = 1; // Falso alarme, reinicia a contagem
                else estado = 0;
                break;
            case 4: // Aguarda asfalto (1)
                if (tipo == 1) estado = 5;
                else estado = 0;
                break;
            case 5: // Aguarda 3ª listra Branca (3)
                if (tipo == 3) estado = 6;
                else if (tipo == 1) estado = 1;
                else estado = 0;
                break;
            case 6: // Aguarda asfalto saindo da faixa (1)
                if (tipo == 1) return 1; // ACHOU A FAIXA DE PEDESTRE!
                else estado = 0;
                break;
        }
        Aux = Aux->Prox;
    }
    return 0;
}

/* ========================================================================= */
/* 4. MAIN - CONTROLANDO AS MÚLTIPLAS DETECÇÕES                              */
/* ========================================================================= */
int main() {
    int L;
    if (scanf("%d", &L) != 1) return 0;

    // Flags para sabermos o que foi detectado no final da imagem
    int achouPlacaPare = 0;
    int achouPlacaAmarela = 0;
    int achouFaixa = 0;

    for (int p = 0; p < L; p++) {
        int n;
        scanf("%d", &n);
        
        TipoLista listaSegmentos;
        FLVazia(&listaSegmentos);

        if (n > 0) {
            int valorAtual;
            scanf("%d", &valorAtual);
            int tipoAtual = mapearCor(valorAtual);
            int contagem = 1;

            // Comprime os pixels
            for (int i = 1; i < n; i++) {
                int valor;
                scanf("%d", &valor);
                int tipo = mapearCor(valor);
                
                if (tipo == tipoAtual) {
                    contagem++;
                } else {
                    TipoItem novo;
                    novo.tipo = tipoAtual;
                    novo.quantidade = contagem;
                    Insere(novo, &listaSegmentos);
                    
                    tipoAtual = tipo;
                    contagem = 1;
                }
            }
            TipoItem ultimo;
            ultimo.tipo = tipoAtual;
            ultimo.quantidade = contagem;
            Insere(ultimo, &listaSegmentos);
        }

        // =====================================================================
        // Testando a linha atual em todas as nossas DFAs
        // =====================================================================
        
        // 1. Procura Placa Vermelha (Borda 2, Meio 3)
        if (!achouPlacaPare) {
            if (verificaPlacaDFA(listaSegmentos, 2, 3)) achouPlacaPare = 1;
        }

        // 2. Procura Placa Amarela (Borda 4, Meio 1)
        if (!achouPlacaAmarela) {
            if (verificaPlacaDFA(listaSegmentos, 4, 1)) achouPlacaAmarela = 1;
        }

        // 3. Procura Faixa de Pedestre
        if (!achouFaixa) {
            if (verificaFaixaPedestreDFA(listaSegmentos)) achouFaixa = 1;
        }

        // Limpeza de memória do perfil
        TipoItem lixo;
        while (!Vazia(listaSegmentos)) {
            Retira(listaSegmentos.Primeiro, &listaSegmentos, &lixo);
        }
        free(listaSegmentos.Primeiro);
    }


    if (achouPlacaPare) printf("Resultado: Placa de PARE detectada.\n");
    if (achouPlacaAmarela) printf("Resultado: Placa amarela detectada.\n");
    if (achouFaixa) printf("Resultado: Faixa de pedestres detectada.\n");
    
    if (!achouPlacaPare && !achouPlacaAmarela && !achouFaixa) {
        printf("Resultado: Nenhum objeto detectado.\n");
    }

    return 0;
}