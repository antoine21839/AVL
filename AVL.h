#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _Noeud{
    int val;
    unsigned int hauteur;
    struct _Noeud *fg;
    struct _Noeud *fd;
}Noeud, *Arbre;

Noeud *alloue_noeud(int val);
int ajouter_noeud(Arbre *a, int val);
Noeud *recherche(const Arbre a, int val);
void liberer_arbre(Arbre a);
void afficher_prefixe(Arbre a);
