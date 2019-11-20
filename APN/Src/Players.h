#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>


typedef struct{
    int idPlayer;
    char nick[30];
    bool active;
    double totalTime;
}Player;


bool loadPlayer(char playerNick[]);
int searchLastID();
bool checkPlayer(char playerNick[]);
void printPlayer(Player p);
void printFilePlayers();
void activeOrDeactivatePlayer(char playerNick[], bool dato);
void printActiveOrInactivePlayers(bool dato);
void insertInArray(Player a[], int cant, Player dato);
void insertion(Player a[], int cant);
int fromFileToArrayOfPlayers(Player a[], int dim);
void printArrayOfPlayersPlayers(Player a[], int cant);
int searchiDFromName(char nickPlayer[]);
Player gPlayerName(char name[30]);
Player nameFromID(int id);





#endif // PLAYERS_H_INCLUDED
