#include <stdio.h>
#include <stdlib.h>
#include "struct_node.h"
#include <string.h>

int insert_new_node(Node **rootPointer, int wishedRA, char *wishedName, double studentFrequency, int *repetitionFound);
int show_tree_order_asc(Node *rootPointer);
int search_by_RA(Node *rootPointer, int wishedRA, char *nameFound, double *frequencyFound);
int remove_student(Node **rootPointer, int wishedRA);
void transplant_old_node_for_another(Node **rootPointer, Node **oldNode, Node **transplantedNode);

Node *get_node_by_RA(Node *rootPointer, int wishedRA, int *nodeFound);
Node *get_tree_minimum_value(Node *rootPointer);
Node *get_tree_max_value(Node *rootPointer);
Node *get_node_successor(Node *rootPointer);
Node *get_node_predecessor(Node *rootPointer);

/* TABELA DE ERROS

1 - insercao ja realizada na arvore
2 - arvore vazia
3 - dado indicado nao existe na arvore

*/

/******************
INSERCOES NA ARVORE
*******************/
int insert_new_node(Node **rootPointer, int wishedRA, char *wishedName, double studentFrequency, int *repetitionFound)
{
    if (*rootPointer == NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        // criando novo node
        newNode->RA = wishedRA;
        strcpy(newNode->name, wishedName);
        newNode->frequency = studentFrequency;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;

        // adicionando na nossa arvore
        *rootPointer = newNode;
        return 0;
    }

    Node *cursor = *rootPointer;

    if (wishedRA == cursor->RA)
    {
        (*repetitionFound) = 1;
        return 1; // aluno ja inserido
    }

    if (wishedRA < cursor->RA && cursor->left != NULL)
    {
        insert_new_node(&cursor->left, wishedRA, wishedName, studentFrequency, repetitionFound);
        if ((*repetitionFound) == 1)
        {
            return 1;
        }

        return 0;
    }
    if (wishedRA > cursor->RA && cursor->right != NULL)
    {
        insert_new_node(&cursor->right, wishedRA, wishedName, studentFrequency, repetitionFound);
        if ((*repetitionFound) == 1)
        {
            return 1;
        }

        return 0;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->RA = wishedRA;
    strcpy(newNode->name, wishedName);
    newNode->frequency = studentFrequency;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = cursor; // cursor representa meu atual pai

    if (newNode->RA < newNode->parent->RA)
    {
        cursor->left = newNode;
    }
    else
    {
        cursor->right = newNode;
    }
}

/******************
MOSTRAR PERCURSO EM ORDEM DA ARVORE
*******************/
int show_tree_order_asc(Node *rootPointer)
{
    if (rootPointer != NULL)
    {

        show_tree_order_asc(rootPointer->left);

        printf("------------------------------------------RA ");
        printf("%d\n", rootPointer->RA);
        printf("%s\n", rootPointer->name);
        printf("Assiduidade: %.2f\n\n", rootPointer->frequency);

        show_tree_order_asc(rootPointer->right);
    }
}

/******************
BUSCA DE ALUNO NA ARVORE POR RA
*******************/
int search_by_RA(Node *rootPointer, int wishedRA, char *nameFound, double *frequencyFound)
{
    if (rootPointer == NULL)
    {
        return 2; // arvore vazia
    }
    int nodeFound = 0;
    Node *cursor = get_node_by_RA(rootPointer, wishedRA, &nodeFound);

    if (cursor != NULL)
    {
        strcpy(nameFound, cursor->name);
        (*frequencyFound) = cursor->frequency;

        return 0;
    }
    return 3; // aluno desejado nao existe na arvore
}

Node *get_node_by_RA(Node *rootPointer, int wishedRA, int *nodeFound)
{

    while ((*nodeFound) != 1)
    {
        if (rootPointer->RA == wishedRA)
        {

            (*nodeFound) = 1;
            return rootPointer; // node encontrado
        }

        if (wishedRA < rootPointer->RA)
        {
            rootPointer = rootPointer->left;
            if (rootPointer == NULL)
            {
                return rootPointer; // chegou em noh folha e nao encontrou o noh desejado
            }
        }

        if (wishedRA > rootPointer->RA)
        {
            rootPointer = rootPointer->right;
            if (rootPointer == NULL)
            {
                return rootPointer; // chegou em noh folha e nao encontrou o noh desejado
            }
        }
    }
}

/******************
REMOCAO DE ALUNO NA ARVORE POR RA
*******************/
Node *get_tree_minimum_value(Node *rootPointer)
{
    while (rootPointer->left != NULL)
    {
        rootPointer = rootPointer->left;
    }

    return rootPointer;
}

Node *get_tree_max_value(Node *rootPointer)
{
    while (rootPointer->right != NULL)
    {
        rootPointer = rootPointer->right;
    }

    return rootPointer;
}

Node *get_node_successor(Node *rootPointer)
{
    if (rootPointer->right != NULL)
    {
        return get_tree_minimum_value(rootPointer->right);
    }

    Node *currentParent = rootPointer->parent;
    // vamos agora "escalar" a arvore, atraves dos ponteiros para pai
    while (rootPointer->parent != NULL && rootPointer == currentParent->right)
    {
        rootPointer = currentParent;
        currentParent = currentParent->parent;
    }

    return currentParent;
}

Node *get_node_predecessor(Node *rootPointer)
{
    if (rootPointer->left != NULL)
    {
        return get_tree_max_value(rootPointer->left);
    }

    Node *currentParent = rootPointer->parent;
    // vamos agora "escalar" a arvore, atraves dos ponteiros para pai
    while (rootPointer->parent != NULL && rootPointer == currentParent->left)
    {
        rootPointer = currentParent;
        currentParent = currentParent->parent;
    }

    return currentParent;
}

void transplant_old_node_for_another(Node **rootPointer, Node **oldNode, Node **transplantedNode)
{
    if ((*oldNode)->parent == NULL)
    {
        (*rootPointer) = *transplantedNode;
    }
    else if ((*oldNode) == (*oldNode)->parent->left)
    {
        (*oldNode)->parent->left = *transplantedNode;
    }
    else
    {
        (*oldNode)->parent->right = *transplantedNode;
    }

    // atualizando novo pai do node que foi transplantado para nova posicao
    if (*transplantedNode != NULL)
    {
        (*transplantedNode)->parent = (*oldNode)->parent;
    }
}

int remove_student(Node **rootPointer, int wishedRA)
{
    if (*rootPointer == NULL)
    {
        return 2; // arvore vazia
    }
    int nodeFound = 0;
    Node *nodeToBeDeleted = get_node_by_RA(*rootPointer, wishedRA, &nodeFound);
    if (nodeFound == 0)
    {
        return 3; // dado indicado nao existe na arvore
    }

    // casos do no folha ou com apenas um filho
    if (nodeToBeDeleted->left == NULL)
    {
        transplant_old_node_for_another(&(*rootPointer), &nodeToBeDeleted, &(nodeToBeDeleted->right));
        return 0;
    }
    if (nodeToBeDeleted->right == NULL)
    {
        transplant_old_node_for_another(&(*rootPointer), &nodeToBeDeleted, &(nodeToBeDeleted->left));
        return 0;
    }

    Node *cursor = get_tree_minimum_value(nodeToBeDeleted->right);

    if (cursor->parent != nodeToBeDeleted)
    {
        transplant_old_node_for_another(&(*rootPointer), &cursor, &(cursor->right)); // removendo o no folha que, ate o momento, eh o sucessor encontrado para substituir o no escolhido
        cursor->right = nodeToBeDeleted->right;
        cursor->right->parent = cursor;
    }
    transplant_old_node_for_another(&(*rootPointer), &nodeToBeDeleted, &cursor); // atualizando aqueles q se ligavam ao no prestes a ser excluido
    cursor->left = nodeToBeDeleted->left;
    cursor->left->parent = cursor;
    // free(nodeToBeDeleted);
    return 0;
}