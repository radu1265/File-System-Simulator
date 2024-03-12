//ANGHELESCU Radu Mihai 314CB
#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct nod_dir
{
    char nume[MAX];
    struct nod_dir* parinte;
    struct nod_file* arb_fisier; 
    struct nod_dir* sub_directories;
    struct nod_dir* st;
    struct nod_dir* dr;

} nod_dir, *arb_dir;

typedef struct nod_file
{
    char nume[MAX];
    struct nod_dir* dir_parinte;
    struct nod_file* st;
    struct nod_file* dr;
} nod_file, *arb_file;

arb_dir init_ROOT();
arb_dir init_dir_arb(char *s, arb_dir parinte);
int cautare_dir(char *s, nod_dir* root);
int inserare_dir(arb_dir arb, char *s, arb_dir dir_parinte); //mkdir
void afisare_dir(arb_dir arb);
arb_dir min_dir(arb_dir arb);
void free_dir(arb_dir arb);

arb_file init_file_arb(char *s, arb_dir parinte);
int inserare_file(arb_file arb, char *s, arb_dir dir_parinte); //touch
int cautare_file(char *s, nod_file* root_file);
void afisare_file(arb_file arb);
arb_file min_file(arb_file arb);
void free_file(arb_file arb);
#endif
