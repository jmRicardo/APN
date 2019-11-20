#ifndef SCOREPLAYER_H_INCLUDED
#define SCOREPLAYER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "MatchList.h"
#include "ScorePlayer.h"


typedef struct _NodoScorePlayerTree{
    scorePLayer dato;
    struct _NodoScorePlayerTree * izquierda;
    struct _NodoScorePlayerTree * derecha;
}NodoScorePlayerTree;

typedef struct _nodoListaScorePlayer{
    scorePLayer dato;
    struct _nodoListaScorePlayer * siguiente;
}nodoListaScorePlayer;




NodoScorePlayerTree * inicArbol();
NodoScorePlayerTree * createNodoTree (scorePLayer dato);
NodoScorePlayerTree * insertTree(NodoScorePlayerTree * tree, NodoScorePlayerTree * nuevo);
NodoScorePlayerTree * searchTree(NodoScorePlayerTree * tree, scorePLayer dato);
void postorder(NodoScorePlayerTree * tree);
void inorder(NodoScorePlayerTree * tree);
void preorder(NodoScorePlayerTree * tree);
void printScoreOfCertainPlayer(char nickPlayer[]);
NodoScorePlayerTree * borrarNodo(NodoScorePlayerTree * arbol, int dato);
NodoScorePlayerTree * nodoMasDerecha(NodoScorePlayerTree * arbol);
NodoScorePlayerTree * nodoMasIzquierda(NodoScorePlayerTree * arbol);


nodoListaScorePlayer * moveFromTreeToLista(NodoScorePlayerTree * tree, nodoListaScorePlayer * lista);

nodoListaScorePlayer * inicListaScore();
nodoListaScorePlayer * createNodoLista(scorePLayer dato);
nodoListaScorePlayer * addToBeginningListeScore(nodoListaScorePlayer * lista, nodoListaScorePlayer * nuevoNodo);
NodoScorePlayerTree * fromFileToTree();

#endif // SCOREPLAYER_H_INCLUDED

