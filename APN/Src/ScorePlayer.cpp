#include "MatchList.h"
#include "Players.h"
#include "ScorePlayer.h"


NodoScorePlayerTree * inicArbol(){   ///funcion que inicia el arbol en NULL
return NULL;
}

NodoScorePlayerTree * createNodoTree (scorePLayer dato){   ///funcion que crea un nodo

NodoScorePlayerTree * aux = (NodoScorePlayerTree*) malloc(sizeof(NodoScorePlayerTree));
aux->dato = dato;
aux->izquierda = NULL;
aux->derecha = NULL;
return aux;
}

NodoScorePlayerTree * insertTree(NodoScorePlayerTree * tree, NodoScorePlayerTree * nuevo){   ///funcion que inserta un nodo en el arbol

    if(tree == NULL)
        tree = nuevo;
    else{
        if (nuevo->dato.idPlayer > tree->dato.idPlayer)
            tree->derecha = insertTree(tree->derecha, nuevo);
    else
            tree->izquierda = insertTree(tree->izquierda, nuevo);
}
    return tree;
}

NodoScorePlayerTree * searchTree(NodoScorePlayerTree * tree, scorePLayer dato){   ///funcion de busqueda

NodoScorePlayerTree * reply = NULL;
    if(tree){
        if(dato.idPlayer == tree->dato.idPlayer)
            reply = tree;
        else
            if(dato.idPlayer > tree->dato.idPlayer)
                reply = searchTree(tree->derecha, dato);
            else
                reply = searchTree(tree->izquierda, dato);
}
return reply;
}

void postorder(NodoScorePlayerTree * tree){   ///recorrido postorder
    if(tree){
        postorder(tree->izquierda);
        postorder(tree->derecha);
        printf("\n--------------------------------");
        printScore(tree->dato);
        printf("\n--------------------------------");
    }
}

void inorder(NodoScorePlayerTree * tree){   ///recorrido inorder
    if (tree){
        inorder(tree->izquierda);
        printf("\n--------------------------------");
        printScore(tree->dato);
        printf("\n--------------------------------");
        inorder(tree->derecha);
    }
}
void preorder(NodoScorePlayerTree * tree){   ///recorrido preorder
    if (tree){
        printf("\n--------------------------------");
        printScore(tree->dato);
        printf("\n--------------------------------");
        preorder(tree->izquierda);
        preorder(tree->derecha);
    }
}

nodoListaScorePlayer * moveFromTreeToLista(NodoScorePlayerTree * tree, nodoListaScorePlayer * lista){   ///funcion que pasa del arbol a una lista
    nodoListaScorePlayer * aux = NULL;
    if (tree){
        aux = createNodoLista(tree->dato);
        lista = addToBeginningListeScore(lista, aux);
        lista = moveFromTreeToLista(tree->derecha, lista);
        lista = moveFromTreeToLista(tree->izquierda, lista);
    }
    return lista;
}

nodoListaScorePlayer * inicListaScore(){
    return NULL;
}

nodoListaScorePlayer * createNodoLista(scorePLayer dato){
    nodoListaScorePlayer * aux = (nodoListaScorePlayer*)malloc(sizeof(nodoListaScorePlayer));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodoListaScorePlayer * addToBeginningListeScore(nodoListaScorePlayer * lista, nodoListaScorePlayer * nuevoNodo){
    nuevoNodo->siguiente = lista;
    return nuevoNodo;
}

NodoScorePlayerTree * fromFileToTree(){   ///funcion que pasa del archivo de Match a un arbol binario de Scores
    GameList aux;
    NodoScorePlayerTree * barbol = inicArbol();
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            NodoScorePlayerTree * helper = createNodoTree(aux.player1);
            barbol = insertTree(barbol, helper);
            NodoScorePlayerTree * helper2 = createNodoTree(aux.player2);
            barbol = insertTree(barbol, helper2);
        }
        fclose(archi);
    }
    return barbol;
}

void printScoreOfCertainPlayer(char nickPlayer[]){   ///funcion que imprime el Score de un cierto jugador
    GameList aux;
    int id = searchiDFromName(nickPlayer);
    NodoScorePlayerTree * barbol = inicArbol();
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            if (id == aux.player1.idPlayer){
                printScore(aux.player1);
                printf("\n--------------------------------");
            }else{
                if (id == aux.player2.idPlayer){
                    printScore(aux.player2);
                    printf("\n--------------------------------");
                }
            }
        }
        fclose(archi);
    }
}

NodoScorePlayerTree * borrarNodo(NodoScorePlayerTree * arbol, int dato){   ///borra nodo a partir de un Id
    if (arbol){
        if (arbol->dato.idPlayer == dato){
            NodoScorePlayerTree * aux = NULL;
            if (arbol->izquierda){
                aux = nodoMasDerecha(arbol->izquierda);
                arbol->dato.idPlayer = aux->dato.idPlayer;
                arbol->izquierda = borrarNodo(arbol->izquierda, aux->dato.idPlayer);
            }
            else if(arbol->derecha){

                aux = nodoMasIzquierda(arbol->derecha);
                arbol->dato.idPlayer = aux->dato.idPlayer;
                arbol->derecha = borrarNodo(arbol->derecha, aux->dato.idPlayer);
            }
            else
            {
                free(arbol);
                arbol = NULL;
            }
        }
        else if (dato < arbol->dato.idPlayer)
        {
            arbol->izquierda = borrarNodo(arbol->izquierda, dato);
        }
        else
        {
           arbol->derecha = borrarNodo(arbol->derecha, dato);
        }

    }
    return arbol;
}





NodoScorePlayerTree * nodoMasDerecha(NodoScorePlayerTree * arbol)    ///funcion auxiliar para la de borrar un nodo
{
    if (arbol){
        if (arbol->derecha)
            nodoMasDerecha(arbol->derecha);
        else
            return arbol;
    }
}

NodoScorePlayerTree * nodoMasIzquierda(NodoScorePlayerTree * arbol)   ///funcion auxiliar para la de borrar un nodo, otra forma de hacerlo (la correcta segun el profe xd)
{
    NodoScorePlayerTree * rta=NULL;
    if (arbol){
        if (arbol->izquierda)
            rta=nodoMasIzquierda(arbol->izquierda);
        else
            rta= arbol;
    }
    return rta;
}













