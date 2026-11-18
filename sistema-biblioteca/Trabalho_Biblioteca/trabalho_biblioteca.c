#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// ---------------- DECLARACOES DE DEFINES ---------------- 
#define TAM_STRING 101
#define TAM_VETOR 10

#define MAX_LIVROS 20
#define MAX_USUARIOS 10
#define MAX_RESERVAS 20

// ---------------- DECLARACOES DE STRUCTS ---------------- 
struct Autor {
    char nome[TAM_STRING];
    char instituicao[TAM_STRING];
};

struct Livro {
    int identificador;
    char titulo[TAM_STRING];
    struct Autor autores;
    int ano;
    int edicao;
    char editora[TAM_STRING];
};

struct Endereco {
    char rua[TAM_STRING];
    int numero;
    char bairro[TAM_STRING];
    char cidade[TAM_STRING];
    char estado[TAM_STRING];
    char pais[TAM_STRING];
};

struct Usuario {
    int identificador;
    char nome[TAM_STRING];
    struct Endereco endereco;
    char telefone[TAM_STRING];
};

struct Reserva {
    int dataInicio;
    int dataFim;
    int identificadorUsuario;
    int identificadorLivro;
};

// ---------------- DECLARACOES DE TYPEDEFS ---------------- 
typedef struct Autor Autor;
typedef struct Livro Livro;
typedef struct Endereco Endereco;
typedef struct Usuario Usuario;
typedef struct Reserva Reserva;

// ---------------- DECLARACOES DE FUNCOES ----------------  
void menu();

void incluirUsuarios(Usuario **usuarios, int *totalUsuarios, int *contador);
void alterarUsuario(Usuario **usuarios, int *totalUsuarios, int n);
void listarUsuarios(Usuario *usuarios, int totalUsuarios);
void excluirUsuarios(Usuario **usuarios, int *totalUsuarios);

void incluirLivros(Livro **livros, int *totalLivros);
void listarLivros(Livro *livros, int totalLivros);

// ---------------- MAIN PRINCIPAL DO CODIGO ----------------  
int main() {

    menu();
    return 0;
}

// ---------------- FUNCOES DO CODIGO ----------------
void menu() {
    // Vetores de armazenamento principais
    int totalUsuarios = 0, contador = 0;
    //int totalLivros = 0;

    Usuario *usuarios;
    usuarios = (Usuario *) malloc(1 * sizeof(Usuario));

    // Livro *livros;
    // livros = (Livro *) malloc(1 * sizeof(Livro));

    // Loop Principal
    while (1) {
        // Declaracoes Principais
        int n;
        printf("\n--------------------\n1 - Usuario\n2 - Livros\n3 - Reserva\n4 - Relatorios\n5 - Sair\nEscolha uma opcao: \n");
        scanf("%d", &n);
        getchar();
        // Condicionais Principais
        if (n == 1) { // Parte de Usuarios
            printf("Entrando na parte de Usuarios...\n");
            // Loop Usuarios
            while (1) {
                printf("\n--------------------\n1 - Incluir\n2 - Alterar\n3 - Excluir\n4 - Voltar\nEscolha uma opcao: \n");
                scanf("%d", &n);
                // Condicionais de Operacao
                if (n == 1) {
                    printf("Incluindo Usuario...\n");
                    incluirUsuarios(&usuarios, &totalUsuarios, &contador);
                } else if (n == 2) {
                    printf("Alterando Usuario...\n");
                    // Loop Alterar Usuarios
                    while (1) {
                        printf("\n--------------------\n1 - Alterar nome\n2 - Alterar endereco\n3 - Alterar telefone\n4 - Voltar\nEscolha uma opcao: \n");
                        scanf("%d", &n);
                        // Condicionais de Operacao
                        if (n == 1) {
                            listarUsuarios(usuarios, totalUsuarios);
                            alterarUsuario(&usuarios, &totalUsuarios, 1);
                        } else if (n == 2) {
                            listarUsuarios(usuarios, totalUsuarios);
                            alterarUsuario(&usuarios, &totalUsuarios, 2);
                        } else if (n == 3) {
                            listarUsuarios(usuarios, totalUsuarios);
                            alterarUsuario(&usuarios, &totalUsuarios, 3);
                        } else if (n == 4) {
                            printf("Saindo da parte de Altercoes...\n");
                            break;
                        } else {
                            printf("ERRO - Digite uma opcao valida\n");
                        }
                    }
                } else if (n == 3) {
                    printf("Excluir Usuario...\n");
                    listarUsuarios(usuarios, totalUsuarios);
                    excluirUsuarios(&usuarios, &totalUsuarios);
                } else if (n == 4) {
                    printf("Saindo da parte de Usuarios...\n");
                    break;
                } else {
                    printf("ERRO - Digite uma opcao valida\n");
                }
            }
        } else if (n == 2) { // Parte de Livros
            printf("Entrando na parte de Livros...\n");
            // Loop Livros e Autores
            while (1) {
                printf("\n--------------------\n1 - Livros\n2 - Autores\n3 - Voltar\nEscolha uma opcao: \n");
                scanf("%d", &n);
                // Condicionais Livros
                if (n == 1) {
                    printf("Entrando na parte de Livros...\n");
                    // Loop Livros
                    while (1) {
                        printf("\n--------------------\n1 - Incluir\n2 - Alterar\n3 - Excluir\n4 - Voltar\nEscolha uma opcao: \n");
                        scanf("%d", &n);
                        // Condicionais de Operacao
                        if (n == 1) {
                            printf("Incluindo Livro...\n");
                            // incluirLivros(&livros, &totalLivros);
                        } else if (n == 2) {
                            printf("Alterando Livro...\n");
                        } else if (n == 3) {
                            printf("Excluir Livro...\n");
                        } else if (n == 4) {
                            printf("Saindo da parte de Livros...\n");
                            break;
                        } else {
                            printf("ERRO - Digite uma opcao valida\n");
                        }
                    }
                } else if (n == 2) {
                    printf("Entrando na parte de Autores...\n");
                    // Loop Autores
                    while (1) {
                        printf("\n--------------------\n1 - Incluir\n2 - Alterar\n3 - Excluir\n4 - Voltar\nEscolha uma opcao: \n");
                        scanf("%d", &n);
                        // Condicionais de Operacao
                        if (n == 1) {
                            printf("Incluindo Autor...\n");
                        } else if (n == 2) {
                            printf("Alterando Autor...\n");
                        } else if (n == 3) {
                            printf("Excluir Autor...\n");
                        } else if (n == 4) {
                            printf("Saindo da parte de Autores...\n");
                            break;
                        } else {
                            printf("ERRO - Digite uma opcao valida\n");
                        }
                    }
                } else if (n == 3) {
                    printf("Saindo do menu de livros...\n");
                    break;
                } else {
                    printf("ERRO - Digite uma opcao valida\n");
                }
            }
        } else if (n == 3) { // Parte de Reserva
            printf("Entrando na parte de Reserva...\n");
            // Loop Reserva
            while (1) {
                printf("\n--------------------\n1 - Incluir\n2 - Alterar\n3 - Excluir\n4 - Voltar\nEscolha uma opcao: \n");
                scanf("%d", &n);
                // Condicionais de Operacao
                if (n == 1) {
                    printf("Incluindo Reserva...\n");
                } else if (n == 2) {
                    printf("Alterando Reserva...\n");
                } else if (n == 3) {
                    printf("Excluir Reserva...\n");
                } else if (n == 4) {
                    printf("Saindo da parte de Reserva...\n");
                    break;
                } else {
                    printf("ERRO - Digite uma opcao valida\n");
                }
            }
        } else if (n == 4) { // Parte de Relatorios
            printf("Entrando na parte de Relatorios...\n");
            // Loop Relatorio
            while (1) {
                printf("\n--------------------\n1 - Lista de livros\n2 - Listar usuarios\n3 - Lista de usuarios com reserva\n4 - Voltar\nEscolha uma opcao: \n");
                scanf("%d", &n);
                // Condicionais Relatorio
                if (n == 1) {
                    printf("Listando Livros...\n");
                } else if (n == 2) {
                    printf("Listando Usuarios...\n");
                    listarUsuarios(usuarios, totalUsuarios);
                } else if (n == 3) {
                    printf("Listando Usuarios com reserva...\n");
                } else if (n == 4) {
                    printf("Saindo do menu de relatorios...\n");
                    break;
                } else {
                    printf("ERRO - Digite uma opcao valida\n");
                }
            }
        } else if (n == 5) { // Sair da Biblioteca
            printf("Saindo da biblioteca...\n");
            break;
        } else { // Opcao Invalida
            printf("ERRO - Digite uma opcao valida\n");
        }
    }
}

// FUNCOES DO USUARIO
void incluirUsuarios(Usuario **usuarios, int *totalUsuarios, int *contador) {
    while (getchar() != '\n');

    // Verificacao de total de usuarios
    if ((*totalUsuarios) >= MAX_USUARIOS) {
        printf("Erro: limite de usuarios atingido.\n");
        return;
    }

    // Realocacoes de memoria
    (*usuarios) = (Usuario *) realloc((*usuarios), ((*totalUsuarios) + 1) * sizeof(Usuario));

    // Verificacao de alocacao
    if (*usuarios == NULL) {
        printf("Erro ao realocar vetor de usuarios.\n");
        return;
    }

    // Inclusoes
    (*usuarios)[*contador].identificador = (*contador) + 1;
    printf("ID do usuario atribuido automaticamente: %d\n", (*usuarios)[*contador].identificador);


    printf("Digite o nome do Usuario: \n");
    fgets((*usuarios)[*contador].nome, TAM_STRING, stdin);
    (*usuarios)[*contador].nome[strcspn((*usuarios)[*contador].nome, "\n")] = '\0';

    printf("----- AGORA E A PARTE DO SEU ENDERECO -----\n");

    printf("Digite a rua do Usuario: \n");
    fgets((*usuarios)[*contador].endereco.rua, TAM_STRING, stdin);
    (*usuarios)[*contador].endereco.rua[strcspn((*usuarios)[*contador].endereco.rua, "\n")] = '\0';
    
    printf("Digite o numero da casa do Usuario: \n");
    scanf("%d", &(*usuarios)[*contador].endereco.numero);
    getchar();

    printf("Digite o bairro do Usuario: \n");
    fgets((*usuarios)[*contador].endereco.bairro, TAM_STRING, stdin);
    (*usuarios)[*contador].endereco.bairro[strcspn((*usuarios)[*contador].endereco.bairro, "\n")] = '\0';

    printf("Digite a cidade do Usuario: \n");
    fgets((*usuarios)[*contador].endereco.cidade, TAM_STRING, stdin);
    (*usuarios)[*contador].endereco.cidade[strcspn((*usuarios)[*contador].endereco.cidade, "\n")] = '\0';

    printf("Digite o estado do Usuario: \n");
    fgets((*usuarios)[*contador].endereco.estado, TAM_STRING, stdin);
    (*usuarios)[*contador].endereco.estado[strcspn((*usuarios)[*contador].endereco.estado, "\n")] = '\0';
    
    printf("Digite o pais do Usuario: \n");
    fgets((*usuarios)[*contador].endereco.pais, TAM_STRING, stdin);
    (*usuarios)[*contador].endereco.pais[strcspn((*usuarios)[*contador].endereco.pais, "\n")] = '\0';

    printf("----- AGORA E A PARTE DO SEU TELEFONE -----\n");

    printf("Digite o numero de telefone do Usuario: \n");
    fgets((*usuarios)[*contador].telefone, TAM_STRING, stdin);
    (*usuarios)[*contador].telefone[strcspn((*usuarios)[*contador].telefone, "\n")] = '\0';


    printf("Usuario adicionado com sucesso!\n");

    (*contador)++;
    (*totalUsuarios)++;
    return;
}

void listarUsuarios(Usuario *usuarios, int totalUsuarios) {
    printf("\nLista de Usuarios:\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("---------------------------\n");
        printf("ID: %d\n", usuarios[i].identificador);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Telefone: %s\n", usuarios[i].telefone);
        printf("Endereco: %s, %d, %s, %s, %s, %s\n", usuarios[i].endereco.rua, usuarios[i].endereco.numero, usuarios[i].endereco.bairro, usuarios[i].endereco.cidade, usuarios[i].endereco.estado, usuarios[i].endereco.pais
        );
    }
    printf("---------------------------\n");
    return;
}

void alterarUsuario(Usuario **usuarios, int *totalUsuarios, int n) {
    int id, encontrado = 0;
    while (encontrado == 0) {
        printf("Digite o id do usuario que deseja alterar: \n");
        scanf("%d", &id);
        getchar();
        for (int i = 0; i < *totalUsuarios; i++) {
            if ((*usuarios)[i].identificador == id) {
                encontrado = 1;
                if (n == 1) {
                    printf("Digite o novo nome do Usuario: \n");
                    fgets((*usuarios)[i].nome, TAM_STRING, stdin);
                    (*usuarios)[i].nome[strcspn((*usuarios)[i].nome, "\n")] = '\0';
                } else if (n == 2) {
                    printf("Agora sera digitado o novo endereco\n");

                    printf("Digite a nova rua do Usuario: \n");
                    fgets((*usuarios)[i].endereco.rua, TAM_STRING, stdin);
                    (*usuarios)[i].endereco.rua[strcspn((*usuarios)[i].endereco.rua, "\n")] = '\0';

                    printf("Digite o novo numero da casa do Usuario: \n");
                    scanf("%d", &(*usuarios)[i].endereco.numero);
                    getchar();

                    printf("Digite o novo bairro do Usuario: \n");
                    fgets((*usuarios)[i].endereco.bairro, TAM_STRING, stdin);
                    (*usuarios)[i].endereco.bairro[strcspn((*usuarios)[i].endereco.bairro, "\n")] = '\0';

                    printf("Digite a nova cidade do Usuario: \n");
                    fgets((*usuarios)[i].endereco.cidade, TAM_STRING, stdin);
                    (*usuarios)[i].endereco.cidade[strcspn((*usuarios)[i].endereco.cidade, "\n")] = '\0';

                    printf("Digite o novo estado do Usuario: \n");
                    fgets((*usuarios)[i].endereco.estado, TAM_STRING, stdin);
                    (*usuarios)[i].endereco.estado[strcspn((*usuarios)[i].endereco.estado, "\n")] = '\0';

                    printf("Digite o novo pais do Usuario: \n");
                    fgets((*usuarios)[i].endereco.pais, TAM_STRING, stdin);
                    (*usuarios)[i].endereco.pais[strcspn((*usuarios)[i].endereco.pais, "\n")] = '\0';
                } else {
                    printf("Digite o novo telefone do Usuario: \n");
                    fgets((*usuarios)[i].telefone, TAM_STRING, stdin);
                    (*usuarios)[i].telefone[strcspn((*usuarios)[i].telefone, "\n")] = '\0';
                }
                
            }
        }
        if (encontrado == 0) printf("Usuario nao encontrado!!! ID Invalido\n");
    }
}

void excluirUsuarios(Usuario **usuarios, int *totalUsuarios) {
    int id, encontrado = 0;

    if (*totalUsuarios == 0) {
        printf("Nenhum usuario cadastrado para excluir.\n");
        return;
    }
    
    while (encontrado == 0) {
        printf("Digite o id do usuario que deseja excluir: \n");
        scanf("%d", &id);
        getchar();
        for (int i = 0; i < *totalUsuarios; i++) {
            if ((*usuarios)[i].identificador == id) {
                encontrado = 1;
                printf("Usuario que esta sendo excluido: \n");
                printf("---------------------------\n");
                printf("ID: %d\n", (*usuarios)[i].identificador);
                printf("Nome: %s\n", (*usuarios)[i].nome);
                printf("Telefone: %s\n", (*usuarios)[i].telefone);
                printf("Endereco: %s, %d, %s, %s, %s, %s\n", (*usuarios)[i].endereco.rua, (*usuarios)[i].endereco.numero, (*usuarios)[i].endereco.bairro, (*usuarios)[i].endereco.cidade, (*usuarios)[i].endereco.estado, (*usuarios)[i].endereco.pais);
                printf("---------------------------\n");
                
                for (int j = i; j < (*totalUsuarios) - 1;j++) {
                    (*usuarios)[j] = (*usuarios)[j + 1];
                }

                (*totalUsuarios)--;

                *usuarios = realloc(*usuarios, (*totalUsuarios) * sizeof(Usuario));
                if (*totalUsuarios > 0 && *usuarios == NULL) {
                    printf("Erro ao realocar memoria para exclusao.\n");
                }

                return;
            }
        }
        if (encontrado == 0) printf("Usuario nao encontrado!!! ID Invalido\n");
    }
}

// FUNCOES DOS LIVROS
/*
void incluirLivros(Livro **livros, int *totalLivros){
    while (getchar() != '\n');

    // Verificacao de total de livros
    if ((*totalLivros) >= MAX_LIVROS) {
        printf("Erro: limite de livros atingido.\n");
        return;
    }

    // Realocacoes de memoria
    (*livros) = (Livro *) realloc((*livros), ((*totalLivros) + 1) * sizeof(Livro));
    
    (*livros)[*totalLivros].titulo = realloc((*livros)[*totalLivros].titulo, 100 * sizeof(char));
    (*livros)[*totalLivros].autores.nome = realloc((*livros)[*totalLivros].autores.nome, 100 * sizeof(char));
    (*livros)[*totalLivros].autores.instituicao = realloc((*livros)[*totalLivros].autores.instituicao, 100 * sizeof(char));
    (*livros)[*totalLivros].editora = realloc((*livros)[*totalLivros].editora, 100 * sizeof(char));

    // Verificacao de alocacao
    if (*livros == NULL) {
        printf("Erro ao realocar vetor de livros.\n");
        return;
    }

    if ((*livros)[*totalLivros].nome == NULL ||
        (*livros)[*totalLivros].telefone == NULL ||
        (*livros)[*totalLivros].endereco.rua == NULL ||
        (*livros)[*totalLivros].endereco.bairro == NULL ||
        (*livros)[*totalLivros].endereco.cidade == NULL ||
        (*livros)[*totalLivros].endereco.estado == NULL ||
        (*livros)[*totalLivros].endereco.pais == NULL) {
        printf("Erro ao realocar memoria para campos de texto.\n");
        return;
    }

    // Inclusoes
    (*livros)[*totalLivros].identificador = *totalLivros + 1;
    printf("ID do usuario atribuido automaticamente: %d\n", (*livros)[*totalLivros].identificador);


    printf("Digite o nome do Usuario: \n");
    fgets((*livros)[*totalLivros].nome, TAM_STRING, stdin);
    (*livros)[*totalLivros].nome[strcspn((*livros)[*totalLivros].nome, "\n")] = '\0';

    printf("----- AGORA E A PARTE DO SEU ENDEREÃÂO -----\n");

    printf("Digite a rua do Usuario: \n");
    fgets((*livros)[*totalLivros].endereco.rua, TAM_STRING, stdin);
    (*livros)[*totalLivros].endereco.rua[strcspn((*livros)[*totalLivros].endereco.rua, "\n")] = '\0';
    
    printf("Digite o numero da casa do Usuario: \n");
    scanf("%d", &(*livros)[*totalLivros].endereco.numero);
    getchar();

    printf("Digite o bairro do Usuario: \n");
    fgets((*livros)[*totalLivros].endereco.bairro, TAM_STRING, stdin);
    (*livros)[*totalLivros].endereco.bairro[strcspn((*livros)[*totalLivros].endereco.bairro, "\n")] = '\0';

    printf("Digite a cidade do Usuario: \n");
    fgets((*livros)[*totalLivros].endereco.cidade, TAM_STRING, stdin);
    (*livros)[*totalLivros].endereco.cidade[strcspn((*livros)[*totalLivros].endereco.cidade, "\n")] = '\0';

    printf("Digite o estado do Usuario: \n");
    fgets((*livros)[*totalLivros].endereco.estado, TAM_STRING, stdin);
    (*livros)[*totalLivros].endereco.estado[strcspn((*livros)[*totalLivros].endereco.estado, "\n")] = '\0';
    
    printf("Digite o pais do Usuario: \n");
    fgets((*livros)[*totalLivros].endereco.pais, TAM_STRING, stdin);
    (*livros)[*totalLivros].endereco.pais[strcspn((*livros)[*totalLivros].endereco.pais, "\n")] = '\0';

    printf("----- AGORA E A PARTE DO SEU TELEFONE -----\n");

    printf("Digite o numero de telefone do Usuario: \n");
    fgets((*livros)[*totalLivros].telefone, TAM_STRING, stdin);
    (*livros)[*totalLivros].telefone[strcspn((*livros)[*totalLivros].telefone, "\n")] = '\0';


    printf("Usuario adicionado com sucesso!\n");

    (*totalLivros)++;
    return;
}
*/
void listarLivros(Livro *livros, int totalLivros) {
    printf("\nLista de Livros:\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("---------------------------\n");
        printf("ID: %d\n", livros[i].identificador);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autores: \n");
        printf("Ano: %d\n", livros[i].ano);
        printf("Edicao: %d\n", livros[i].edicao);
        printf("Editora: %s\n", livros[i].editora);
    }
    printf("---------------------------\n");
    return;
}
