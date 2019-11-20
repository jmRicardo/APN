#include "MatchList.h"
#include "Players.h"

int searchLastMatch(){   ///funcion que devuelve el id de la ultima partida jugada
    int id = 0;
    GameList aux;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        if (!(fseek(archi,-1*sizeof(GameList),SEEK_END))){
            fread(&aux, sizeof(GameList), 1, archi);
            id = aux.idMatch;
        }
        fclose(archi);
    }
    return id;
}

void initMatch(Player one, Player two){   ///funcion que inicia una partida
    GameList aux;
    int id = searchLastMatch();
    FILE * archi = fopen("MatchFile.dat", "ab");
    if (archi){
        aux.idMatch = id + 1;
        aux.player1.idPlayer = one.idPlayer;
        aux.player1.matchTime = aux.player2.matchTime = 0;
        aux.player1.wins = aux.player2.wins = 0;
        aux.player2.idPlayer = two.idPlayer;
        fwrite(&aux, sizeof(GameList), 1, archi);
        fclose(archi);
    }
}

void printScore(scorePLayer score){   ///funcion que muestra un solo Score
    printf("\n Id Player: %d", score.idPlayer);
    printf("\nMatch Time: %lf", score.matchTime);
    printf("\nWins      : %d", score.wins);
}

void printMatch(GameList match){   ///funcion auxiliar que muestra un solo Match
    printf("\n  Id Match: |%d|", match.idMatch);
    printScore(match.player1);
    printScore(match.player2);
}

void printMatchFile(){   ///funcion que muestra por pantalla todos los Matches jugados
    GameList aux;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            printMatch(aux);
            printf("\n--------------------------------------------");
        }
        fclose(archi);
    }
}

Player traeme(){  ///funcion auxiliar para cargar un player
    Player aux;
    FILE * archi = fopen("players.dat", "rb");
    if (archi){
        fseek(archi, 1*sizeof(Player), SEEK_SET);
        fread(&aux, sizeof(Player), 1, archi);
        fclose(archi);
    }
    return aux;
}

Player traemeotro(){   ///funcion auxiliar para cargar un player
    Player aux;
    FILE * archi = fopen("players.dat", "rb");
    if (archi){
        fseek(archi, 2*sizeof(Player), SEEK_SET);
        fread(&aux, sizeof(Player), 1, archi);
        fclose(archi);
    }
    return aux;
}

nodoGameList * inicLista(){   ///inicia lista en NULL
    return NULL;
}

nodoGameList * createNodo(GameList dato){   ///crea un nodo
    nodoGameList * aux = (nodoGameList*)malloc(sizeof(nodoGameList));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodoGameList * addToBeginning(nodoGameList * lista, nodoGameList * nuevoNodo){   ///añade al principio de la lista
    nuevoNodo->siguiente = lista;
    return nuevoNodo;
}

nodoGameList * searchLastNodo(nodoGameList * lista){   ///buscar ultimo nodo de la lista
    nodoGameList * aux = lista;
    if (aux){
        while (aux->siguiente){
            aux = aux->siguiente;
        }
    }
    return aux;
}

nodoGameList * addToFinal(nodoGameList * lista, nodoGameList * nuevoNodo){   ///añade al final de la lista
    if (lista == NULL){
        lista = nuevoNodo;
    }else{
        nodoGameList * aux = searchLastNodo(lista);
        aux->siguiente = nuevoNodo;
    }
    return lista;
}

nodoGameList * searchNodoForIdPlayer(nodoGameList * lista, int idPlayer){   ///busca un nodo que tenga un id igual al enviado
    nodoGameList * aux = lista;
    while (aux && aux->dato.player1.idPlayer != idPlayer){
        aux = aux->siguiente;
    }
    return aux;
}

int fromFileToArray(cell adl[], int dim){   ///pasa del archivo al arreglo de listas (con las listas en NULL)
    Player aux;
    int i = 0;
    FILE * archi = fopen("players.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(Player), 1, archi) > 0){
            adl[i].dato = aux;
            adl[i].lista = inicLista();
            i++;
        }
        fclose(archi);
    }
    return i;
}

void printArrayOfPlayers(cell adl[], int cant){   ///imprime por pantalla el arreglo de players
    int i = 0;
    for (i=0; i<cant; i++){
        printPlayer(adl[i].dato);
    }
}

int searchPosInArray(cell adl[], int validos, int idPlayer){   ///busca la posicion de un player en el arreglo
    int pos = -1;
    int i = 0;
    while (i < validos && pos == -1){
        if (adl[i].dato.idPlayer == idPlayer){
            pos = i;
        }
        i++;
    }
    return pos;
}

int addToArray(cell adl[], int validos, int idPlayer){   ///añade al arreglo
    adl[validos].dato.idPlayer = idPlayer;
    adl[validos].lista = inicLista();
    return validos + 1;
}

int alta(cell adl[], int validos, int idPlayer, GameList dato){   ///agrega un dato de tipo GameList
    nodoGameList * aux = createNodo(dato);
    int pos = searchPosInArray(adl, validos, idPlayer);
    if (pos == - 1){
        validos = addToArray(adl, validos, idPlayer);
        pos = validos - 1;
    }
    adl[pos].lista = addToFinal(adl[pos].lista, aux);
    return validos;
}

int listaToArrayOfPlayers(cell adl[], int cant){   ///pasa del archivo de Matches al arreglo de listas
    GameList aux;
    int validos = 0;
    int i = 0;
    int j = 0;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            nodoGameList * helper1 = createNodo(aux);
            nodoGameList * helper2 = createNodo(aux);
            validos = alta(adl, cant, helper1->dato.player1.idPlayer, aux);
            validos = alta(adl, cant, helper2->dato.player2.idPlayer, aux);
        }
        fclose(archi);
    }
    return validos;
}

void printArrayOfPlayersWithListas(cell adl[], int cant){   ///muestra el arreglo de listas
    int i = 0;
    for (i=0; i<cant; i++){
        printf("\n--------------------------------------------");
        printPlayer(adl[i].dato);
        printf("\n--------------------");
        printf("\nMatches de: %s", adl[i].dato.nick);
        printf("\n--------------------");
        if (adl[i].lista){
            nodoGameList * aux = adl[i].lista;
            while (aux){
                printMatch(aux->dato);
                printf("\n--------------------");
                aux = aux->siguiente;
            }
        }
        printf("\n--------------------------------------------\n");
    }
}

void printMatchFromAnId(int iD){   ///muestra un Match buscado por su Id
    GameList aux;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        fseek(archi, ((iD - 1)*(sizeof(GameList))), SEEK_SET);
        fread(&aux, sizeof(GameList), 1, archi);
        printf("\n--------------------------------------------");
        printMatch(aux);
        printf("\n--------------------------------------------");
        fclose(archi);
    }
}

void printMatchFromAplayer(char nickPlayer[]){   ///muestra todos los Matches de un jugador especifico
    GameList aux;
    int id = searchiDFromName(nickPlayer);
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            if (aux.player1.idPlayer == id || aux.player2.idPlayer == id){
                printMatch(aux);
                printf("\n--------------------------------------------");
            }
        }
        fclose(archi);
    }
}

int matchesPlayed(char nickPlayer[]){   ///devuelve la cantidad de partidas que jugo un Player
    GameList aux;
    int cantidad = 0;
    int id = searchiDFromName(nickPlayer);
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            if (aux.player1.idPlayer == id || aux.player2.idPlayer == id){
                cantidad++;
            }
        }
        fclose(archi);
    }
    return cantidad;
}

double playedTime(char nickPlayer[]){   ///cantidad total de tiempo que jugo un player
    GameList aux;
    int id = searchiDFromName(nickPlayer);
    double total = 0;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            if (id == aux.player1.idPlayer){
                total = total + aux.player1.matchTime;
                }
            if (id == aux.player2.idPlayer){
                total = total + aux.player2.matchTime;
            }
        }
        fclose(archi);
    }
    return total;
}

void cargaGameList(){   ///funcion auxiliar de carga de GameList
    GameList aux;
    char control = 's';
    FILE * archi = fopen("MatchFile.dat", "ab");
    if (archi){
        while (control == 's'){
            printf("\nId Match: ");
            fflush(stdin);
            scanf("%d", &aux.idMatch);
            printf("\nId Player 1: ");
            scanf("%d", &aux.player1.idPlayer);
            printf("\nMatch time 1: ");
            fflush(stdin);
            scanf("%lf", &aux.player1.matchTime);
            printf("\nWins 1: ");
            scanf("%d", &aux.player1.wins);
            printf("\nId Player 2: ");
            scanf("%d", &aux.player2.idPlayer);
            printf("\nMatch time 2: ");
            fflush(stdin);
            scanf("%lf", &aux.player2.matchTime);
            printf("\nWins 2: ");
            scanf("%d", &aux.player2.wins);

            fwrite(&aux, sizeof(GameList), 1, archi);

            printf("\nSeguir?");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archi);
    }
}

int totalWinsOfAplayer(char nickPlayer[]){    ///funcion que devuelve el total de wins que un Player tiene
    GameList aux;
    int id = searchiDFromName(nickPlayer);
    int total = 0;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(GameList), 1, archi) > 0){
            if (id == aux.player1.idPlayer){
                total = total + aux.player1.wins;
            }
            if (id == aux.player2.idPlayer){
                total = total + aux.player2.wins;
            }
        }
        fclose(archi);
    }
    return total;
}

int whoWonTheScreen(double timePassed, char nickPlayer[]){   ///funcion que carga el tiempo transcurrido de una pantalla y quien gano esa pantalla
    int idP = searchiDFromName(nickPlayer);
    GameList aux;
    FILE * archi = fopen("MatchFile.dat", "r+b");
    if (archi){
            fseek(archi,-1*sizeof(GameList),SEEK_END);   ///me paro en el ultimo Match
            fread(&aux, sizeof(GameList), 1, archi);    ///lo leo y le sumo el win al Player que le corresponda y el tiempo a ambos
        if (idP == aux.player1.idPlayer){
            aux.player1.matchTime += timePassed;
            aux.player2.matchTime += timePassed;
            aux.player1.wins ++;
            fseek(archi,-1*sizeof(GameList),SEEK_END);
            fwrite(&aux, sizeof(GameList), 1, archi);
        }else{
            aux.player1.matchTime += timePassed;
            aux.player2.matchTime += timePassed;
            aux.player2.wins ++;
            fseek(archi,-1*sizeof(GameList),SEEK_END);
            fwrite(&aux, sizeof(GameList), 1, archi);
        }
        fclose(archi);
    }
    return idP;
}

int whoWonTheMatch(){    ///funcion que devuelve el Id del Player que gano el ultimo Match
    int rta;
    GameList aux;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
        fseek(archi, -1*sizeof(GameList), SEEK_END);
        fread(&aux, sizeof(GameList), 1, archi);
        int idP1 = aux.player1.idPlayer;
        int idP2 = aux.player2.idPlayer;
        if (aux.player1.wins > aux.player2.wins){
            rta = idP1;
        }else{
            rta = idP2;
        }
        fclose(archi);
    }
    return rta;
}

int lowestPos(scorePLayer a[], int validos, int pos){   ///funcion auxiliar para el metodo de seleccion
    scorePLayer menor = a[pos];
    int posMenor = pos;
    int i = pos + 1;
    while (i < validos){
        if (menor.wins > a[i].wins){
            menor = a[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}

void seleccion(scorePLayer a[], int validos){   ///seleccion a partir de la strcut Scores
    int i = 0;
    scorePLayer aux;
    int posMenor;
    while (i < validos-1){
        posMenor = lowestPos(a, validos, i);
        aux = a[posMenor];
        a[posMenor] = a[i];
        a[i] = aux;
        i++;
    }
}

int fromFileToArrayOfScores(scorePLayer a[], int dim){   ///funcion que pasa del archivo a un arreglo de Scores
    GameList aux;
    int lastID = searchLastID();
    int i = 0;
    FILE * archi = fopen("MatchFile.dat", "rb");
    if (archi){
            while (i < lastID){
                a[i].idPlayer = i+1;
                a[i].matchTime = 0;
                a[i].wins = 0;
                while (fread(&aux, sizeof(GameList), 1, archi) > 0){
                    if (a[i].idPlayer == aux.player1.idPlayer){
                        a[i].matchTime += aux.player1.matchTime;
                        a[i].wins += aux.player1.wins;
                    }
                    if (a[i].idPlayer == aux.player2.idPlayer){
                        a[i].matchTime += aux.player2.matchTime;
                        a[i].wins += aux.player2.wins;
                    }
                }
                rewind(archi);
                i++;
            }
        fclose(archi);
    }
    return i;
}

void printArrayOfScores(scorePLayer a[], int validos){    ///funcion que imprime un arreglo de Scores
    int i = 0;
    for (i=0; i<validos; i++){
        printf("\n--------------------");
        printScore(a[i]);
        printf("\n--------------------");
    }
}














