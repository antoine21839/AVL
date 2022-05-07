#include "AVL.h"

static unsigned int max(int a, int b){
    if(a > b)
        return a;
    return b;
}

static void maj_hauteur(Arbre a){
    if(NULL == a)
        return;
    if(NULL != a->fg && NULL != a->fd)
        a->hauteur = 1 + max(a->fg->hauteur, a->fd->hauteur);
    else if(NULL != a->fd)
        a->hauteur = 1 + a->fd->hauteur;
    else if(NULL != a->fg)
        a->hauteur = 1 + a->fg->hauteur;
    else
        a->hauteur = 0;
}

static int calcul_balance(Arbre a){
    int bal;

    bal = 0;
    if(NULL != a->fg)
        bal -= a->fg->hauteur;
    else
        ++bal;
    if(NULL != a->fd)
        bal += a->fd->hauteur;
    else
        --bal;
    return bal;
}

Noeud *alloue_noeud(int val){
    Noeud *tmp;
    tmp = (Noeud *)malloc(sizeof(Noeud));
    if (NULL == tmp){
        fprintf(stderr, "Erreur de l'allocation de la mémoire.\n");
        return NULL;
    }
    tmp->fg = NULL;
    tmp->fd = NULL;
    tmp->val = val;
    tmp->hauteur = 0;
    return tmp;
}

static void rotation_D(Arbre *r){
    Arbre g;

    assert(NULL != r);
    assert(NULL != *r);

    g = (*r)->fg;
    --(*r)->hauteur;
    ++g->hauteur;
    (*r)->fg = g->fd;
    g->fd = *r;
    *r = g;
}

static void rotation_G(Arbre *r){
    Arbre d;

    assert(NULL != r);
    assert(NULL != *r);

    d = (*r)->fd;
    --(*r)->hauteur;
    ++d->hauteur;
    (*r)->fd = d->fg;
    d->fg = *r;
    *r = d;
}

static void rotation_DG(Arbre *a){
    assert(NULL != a);
    assert(NULL != *a);

    rotation_D(&(*a)->fd);
    rotation_G(a);
}

static void rotation_GD(Arbre *a){
    assert(NULL != a);
    assert(NULL != *a);

    rotation_G(&(*a)->fg);
    rotation_D(a);
}

static void equilibrer(Arbre *a){
    int balance;

    assert(NULL != a);
    assert(NULL != *a);

    balance = calcul_balance(*a);
    if(balance == 2){
        if(calcul_balance((*a)->fd) >= 0)
            rotation_G(a);
        else
            rotation_DG(a);
    }
    else if(balance == -2){
        if(calcul_balance((*a)->fg) <= 0)
            rotation_D(a);
        else
            rotation_GD(a);
    }
}

int ajouter_noeud(Arbre *a, int val){
    int res;

    assert(NULL != a);

    res = 0;
    if(NULL == *a){
        *a = alloue_noeud(val);
        if(NULL == *a){
            fprintf(stderr, "Erreur d'allocation.\n");
            return 0;
        }
        return 1;
    }
    if(val < (*a)->val)
        res = ajouter_noeud(&(*a)->fg, val);
    else if(val > (*a)->val)
        res = ajouter_noeud(&(*a)->fd, val);
    equilibrer(a);
    maj_hauteur(*a);
    return res;
}

Noeud *recherche(const Arbre a, int val){
    if(NULL == a)
        return NULL;
    if(val < a->val)
        return recherche(a->fg, val);
    if(val > a->val)
        return recherche(a->fd, val);
    return a;
}

int est_dans_arbre(const Arbre a, int val){
    return NULL != recherche(a, val);
}

void liberer_arbre(Arbre a){
    if(NULL == a)
        return;
    liberer_arbre(a->fg);
    liberer_arbre(a->fd);
    free(a);
}

void afficher_prefixe(Arbre a){
    if(NULL == a)
        return;
    afficher_prefixe(a->fg);
    printf("%d\n", a->val);
    afficher_prefixe(a->fd);
}
