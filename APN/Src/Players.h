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
    //double totalTime;
    //double totalScoreTime;
    //int wins;
}Player;

bool loadPlayer(char playerNick[]);
int searchLastID();
bool checkPlayer(char playerNick[]);
void printPlayer(Player p);
void printFilePlayers();


#endif // PLAYERS_H_INCLUDED
