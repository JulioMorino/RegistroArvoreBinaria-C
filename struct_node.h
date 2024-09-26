#ifndef STRUCT_NODE
#define STRUCT_NODE

typedef struct node
{
    int RA;
    char name[64];
    double frequency;

    struct node *left, *right, *parent;
} Node;

#endif