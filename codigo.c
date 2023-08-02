#include <stdio.h>

struct Livro {
    int codigo;
    char titulo[100];
    char autor[50];
    int ano;
};

void cadastrarLivro(FILE *arquivo);
void listarLivros(FILE *arquivo);
void buscarLivro(FILE *arquivo);
void editarLivro(FILE *arquivo);
void excluirLivro(FILE *arquivo);

int main() {
    FILE *arquivo;
    int opcao;

    arquivo = fopen("biblioteca.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    do {
        printf("\n========== MENU ==========\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar livros\n");
        printf("3 - Buscar livro\n");
        printf("4 - Editar livro\n");
        printf("5 - Excluir livro\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarLivro(arquivo);
                break;
            case 2:
                listarLivros(arquivo);
                break;
            case 3:
                buscarLivro(arquivo);
                break;
            case 4:
                editarLivro(arquivo);
                break;
            case 5:
                excluirLivro(arquivo);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida! Digite novamente.\n");
        }
    } while (opcao != 0);

    fclose(arquivo);
    return 0;
}

void cadastrarLivro(FILE *arquivo) {
    struct Livro livro;
    printf("\n== Cadastro de Livro ==\n");
    printf("Codigo: ");
    scanf("%d", &livro.codigo);
    printf("Titulo: ");
    scanf(" %[^\n]", livro.titulo); 
    printf("Autor: ");
    scanf(" %[^\n]", livro.autor); 
    printf("Ano: ");
    scanf("%d", &livro.ano);

    fprintf(arquivo, "%d;%s;%s;%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
    printf("\nLivro Cadastrado com Sucesso\n");
}

void listarLivros(FILE *arquivo) {
    struct Livro livro;
    int quantidadeTotal = 0;

    printf("\n== Lista de Livros ==\n");

    rewind(arquivo); //volta para o inicio do arquivo txt

    while (fscanf(arquivo, "%d;%[^;];%[^;];%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) == 4) {
        quantidadeTotal++;
    }

    printf("Quantidade total de livros: %d\n", quantidadeTotal);

    rewind(arquivo);

    while (fscanf(arquivo, "%d;%[^;];%[^;];%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) == 4) {
        printf("\nCodigo: %d\n", livro.codigo);
        printf("Titulo: %s\n", livro.titulo);
        printf("Autor: %s\n", livro.autor);
        printf("Ano: %d\n", livro.ano);
        printf("--------------------------\n");
    }
}

void buscarLivro(FILE *arquivo) {
    int codigo;
    struct Livro livro;
    int encontrado = 0;

    printf("\n== Buscar Livro por Codigo ==\n");
    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);

    rewind(arquivo);

    while (fscanf(arquivo, "%d;%[^;];%[^;];%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) == 4) {
        if (livro.codigo == codigo) {
            printf("\nCodigo: %d\n", livro.codigo);
            printf("Titulo: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano: %d\n", livro.ano);
            printf("--------------------------\n");
            encontrado = 1;
            break;
        }
    }
    if (encontrado == 0) {
        printf("Livro nao encontrado!\n");
    }
}

void editarLivro(FILE *arquivo) {
    int codigo;
    struct Livro livro;
    FILE *arquivoTemp = fopen("temp.txt", "w");

    printf("\n== Edicao de Livro ==\n");
    printf("Digite o codigo do livro que deseja editar: ");
    scanf("%d", &codigo);

    rewind(arquivo);

    while (fscanf(arquivo, "%d;%[^;];%[^;];%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) == 4) {
        if (livro.codigo == codigo) {
            printf("Novo titulo: ");
            scanf(" %[^\n]", livro.titulo); 

            printf("Novo autor: ");
            scanf(" %[^\n]", livro.autor); 

            printf("Novo ano: ");
            scanf("%d", &livro.ano);

            fprintf(arquivoTemp, "%d;%s;%s;%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
            printf("Livro editado com sucesso!\n");
        } else {
            fprintf(arquivoTemp, "%d;%s;%s;%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);
    remove("biblioteca.txt");
    rename("temp.txt", "biblioteca.txt");

    arquivo = fopen("biblioteca.txt", "a+");
}

void excluirLivro(FILE *arquivo) {
    int codigo;
    struct Livro livro;
    FILE *arquivoTemp = fopen("temp.txt", "w");

    printf("\n== Exclusao de Livro ==\n");
    printf("Digite o codigo do livro que deseja excluir: ");
    scanf("%d", &codigo);

    rewind(arquivo);

    while (fscanf(arquivo, "%d;%[^;];%[^;];%d\n", &livro.codigo, livro.titulo, livro.autor, &livro.ano) == 4) {
        if (livro.codigo == codigo) {
            printf("Livro excluido com sucesso!\n");
        } else {
            fprintf(arquivoTemp, "%d;%s;%s;%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);
    remove("biblioteca.txt");
    rename("temp.txt", "biblioteca.txt");

    arquivo = fopen("biblioteca.txt", "a+");
}
