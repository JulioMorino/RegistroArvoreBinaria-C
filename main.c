#include <stdio.h>
#include <stdlib.h>
#include "struct_node.h"
#include "binaryTreeCRUD.c"

int main()
{
    int userSelect;
    Node *TreeRoot = NULL; // arvore inicialmente vazia
    int RA = 0, errorCode;
    char name[64] = "";
    double studentFrequency = 100.0;
    double frequencyQuery = 0.0;
    int repetitionFound = 0;
    do
    {
        system("cls");
        printf("Arvore Binaria de Busca\n\n");
        printf("\n\nOpcoes: \n\n");
        printf("1 -> Insere um unico dado\n");
        printf("2 -> Visualizar alunos na ordem crescente por RA\n");
        printf("3 -> Buscar aluno pelo RA\n");
        printf("4 -> Remover aluno pelo RA\n");
        printf("5 -> \n");
        printf("6 -> \n");
        printf("7 ->\n");
        printf("0 -> Sair \n:");
        scanf("%d", &userSelect);

        switch (userSelect)
        {
        case 1:
            printf("Insira o RA do aluno: ");
            scanf("%d", &RA);
            getchar();
            printf("Insira um nome para o aluno: ");
            scanf(" %63[^\n]", &name);
            errorCode = insert_new_node(&TreeRoot, RA, name, studentFrequency, &repetitionFound);
            if (errorCode == 1)
                printf("Dado ja existente. Insercao cancelada.\n");
            else
            {
                printf("Operacao realizada com sucesso.\n");
                printf("A raiz atual eh %d\n", TreeRoot->RA);
            }
            system("pause");
            break;
        case 2:
            show_tree_order_asc(TreeRoot);
            system("pause");
            break;

        case 3:
            printf("Insira o RA do aluno que deseja encontrar: ");
            scanf("%d", &RA);
            errorCode = search_by_RA(TreeRoot, RA, name, &frequencyQuery);
            if (errorCode == 0)
            {
                printf("\nBusca realizada com sucesso.");
                printf("------------------------------------------RA ");
                printf("%d\n", RA);
                printf("%s\n", name);
                printf("Assiduidade: %.2f\n\n", frequencyQuery);
            }
            if (errorCode == 3)
                printf("\nDado indicado nao existe na arvore.\n");
            if (errorCode == 2)
                printf("\nArvore vazia.\n");
            system("pause");
            break;

        case 4:
            printf("Insira o RA do aluno que deseja remover: ");
            scanf("%d", &RA);
            errorCode = remove_student(&TreeRoot, RA);
            if (errorCode == 0)
                printf("\nAluno com RA %d foi removido com sucesso da arvore.\n", RA);
            if (errorCode == 2)
                printf("\nArvore vazia, nada foi removido.\n");
            if (errorCode == 3)
                printf("\nDado indicado nao existe na arvore.\n");
            system("pause");
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;
        case 8:
            break;

        case 9:
            break;

        case 0:
            break;

        default:
            printf("\n\n Opcao nao valida");
        }
        getchar(); /* Limpa o buffer de entrada */
    } while ((userSelect != 0));
    system("pause");
}
