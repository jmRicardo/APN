#include "Players.h"
#include <stdbool.h>

/// carga el jugador y devuelve falso si ya existe, usar este dato para mostrar cartel de " YA EXISTE "
bool loadPlayer(char playerNick[]){
    bool flag = checkPlayer(playerNick);
    if (flag)
    {
        Player aux;
        int id = searchLastID() + 1;
        FILE * archi = fopen("players.dat", "ab");
        if (archi)
        {
            aux.idPlayer = id;
            strcpy(aux.nick, playerNick);
            aux.active = true;
            aux.totalTime = 0;
            fwrite(&aux, sizeof(Player), 1, archi);
        }
        fclose(archi);
    }
    return flag;
}

int searchLastID()       /// se para en el ultimo bloque de archivo y retorna su ID
{
    int id = 0;
    Player aux;
    FILE * archi = fopen("players.dat", "rb");
    if (archi)
    {
            fseek(archi, -1*sizeof(Player), SEEK_END);    ///aca saque un if suelto q no se porque estaba
            fread(&aux, sizeof(Player), 1, archi);
            id = aux.idPlayer;
    }
    fclose(archi);
    return id;
}

bool checkPlayer(char playerNick[]){            /// recorre el archivo, lo busca (a un Player), si existe devuelve 0
    FILE * archi = fopen("players.dat", "rb");
    Player aux;
    bool flag = true;
    if (archi){
        while (fread(&aux, sizeof(Player), 1, archi)>0 && flag)
        {
           if (!strcmpi(aux.nick,playerNick))
            flag = false;
        }
    }
    fclose(archi);
    return flag;
}

void printPlayer(Player p)  ///funcion auxiliar que imprime un player por pantalla (con o sin el active)
{
    printf("\n        Id: %d", p.idPlayer);
    printf("\n      Nick: %s", p.nick);
    printf("\n    Active: %d", p.active);
    printf("\nTotal Time: %lf", p.totalTime);
}

void printFilePlayers()   ///imprime por pantalla todos los players desde el archivo
{
    FILE * archi = fopen("players.dat","rb");
    Player aux;
    if (archi)
    {
        while (fread(&aux,sizeof(Player),1,archi)>0)
        {
            printf("\n--------------------");
            printPlayer(aux);
            printf("\n--------------------");
        }
        fclose(archi);
    }

}

void activeOrDeactivatePlayer(char playerNick[], bool dato){   ///funcion que desactiva o activa un Player
    Player aux;
    int iD = searchiDFromName(playerNick);
    FILE * archi = fopen("players.dat", "rb+");
    if (archi){
        fseek(archi, ((iD-1)*sizeof(Player)), SEEK_SET);
        fread(&aux, sizeof(Player), 1, archi);
        aux.active = dato;
        fseek(archi, ((iD-1)*sizeof(Player)), SEEK_SET);
        fwrite(&aux, sizeof(Player), 1, archi);
        fclose(archi);
    }
}

void printActiveOrInactivePlayers(bool dato){   ///imprime Players activos o inactivos
    Player aux;
    FILE * archi = fopen("players.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(Player), 1, archi) > 0){
            if (aux.active == dato){
                printf("\n--------------------");
                printPlayer(aux);
                printf("\n--------------------");
            }
        }
        fclose(archi);
    }
}

void insertInArray(Player a[], int cant, Player dato){   ///funcion auxiliar para el metodo de insercion
    int i = cant;
    while (i >=0 && (strcmpi(dato.nick, a[i].nick) < 0)){
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = dato;
}

void insertion(Player a[], int cant){   ///insercion
    int i = 0;
    while (i < cant-1){
        insertInArray(a, i, a[i + 1]);
        i++;
    }
}

int fromFileToArrayOfPlayers(Player a[], int dim){   ///pasar del archivo a un arreglo de Players
    Player aux;
    int i = 0;
    FILE * archi = fopen("players.dat", "rb");
    if (archi){
        while (fread(&aux, sizeof(Player), 1, archi) > 0){
            a[i] = aux;
            i++;
        }
        fclose(archi);
    }
    return i;
}

void printArrayOfPlayersPlayers(Player a[], int cant){   ///imprimimos un arreglo de Players
    int i = 0;
    for (i=0; i<cant; i++){
        printf("\n--------------------");
        printPlayer(a[i]);
        printf("\n--------------------");
    }
}

int searchiDFromName(char nickPlayer[]){   ///funcion auxiliar que devuelve el iD de un player recibiendo el nick
    FILE * archi = fopen("players.dat", "rb");
    Player aux;
    int iD = -1;
    if (archi){
        while (fread((&aux), sizeof(Player), 1, archi) > 0){
            if (strcmpi(nickPlayer, aux.nick) == 0){
                iD = aux.idPlayer;
            }
        }
        fclose(archi);
    }
    return iD;
}

Player gPlayerName(char name[30])
{
    Player aux;
    FILE * archi = fopen("players.dat", "rb");
    if (archi){
        while (fread((&aux), sizeof(Player), 1, archi) > 0 && strcmpi(name,aux.nick)){}
        fclose(archi);
    }
    return aux;

}

Player nameFromID(int id)
{
    Player aux;
    FILE * archi = fopen("players.dat", "rb");
    if (archi){
        while (fread((&aux), sizeof(Player), 1, archi) > 0 && id!=aux.idPlayer){}
        fclose(archi);
    }
    return aux;
}














