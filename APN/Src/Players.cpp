#include "Players.h"


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
            strcpy(aux.nick,playerNick);
            aux.active = true;
            fwrite(&aux,sizeof(Player),1,archi);
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
        if (fseek(archi,-1*sizeof(Player),SEEK_END))
            fread(&aux,sizeof(Player),1,archi);
        id = aux.idPlayer;
    }
    fclose(archi);
    return id;
}

bool checkPlayer(char playerNick[]){            /// recorre el archivo lo buscar si existe y retorna 0(si no esta) si esta
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
    std::cout << p.idPlayer << std::endl;
    std::cout << p.nick << std::endl;
    //std::cout << p.active << std::endl;
}

void printFilePlayers()   ///imprime por pantalla todos los players desde el archivo
{
    FILE * archi = fopen("players.dat","rb");
    Player aux;
    if (archi)
    {
        while (fread(&aux,sizeof(Player),1,archi)>0)
        {
            printPlayer(aux);
        }
        fclose(archi);
    }

}















