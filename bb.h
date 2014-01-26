#include <stdio.h>
#include <string.h>
#include <math.h>


//#ifndef DATASTRUCTURE_H_INCLUDED
//#define DATASTRUCTURE_H_INCLUDED

typedef struct sPunktlast
{
    float  Position;
    int Richtung; //Rechts=1 Links=0
    float  Last;
    struct sPunktlast *Next;
}TPunktlast;

typedef struct sAeussMoment
{
    //int Position;
    int Richtung; //Rechts=1 Links=0
    float  Last;
    struct sAeussMoment *Next;
}TAeussMoment;

typedef struct sRechtecklast
{
    float  Position_X1;
    float  Position_Last;
    int Richtung;
    float  Laenge;
    float  Hoehe;
    float  Flaechenlast;
    struct sRechtecklast *Next;
}TRechtecklast;

typedef struct sTrapezlast
{
    float  Position_X1;
    float  Position_X2;
    float  Position_Last;
    int Richtung; //uhrzeiger=1  gegen Uhrzeiger=0
    float  Laenge;
    float  Hoehe_X1;
    float  Hoehe_X2;
    float  HoeheDreieck;
    float  Dreieckflaeche;
    struct sTrapezlast *Next;
}TTrapezlast;

typedef struct sLager
{
    float  Position;
    float  Lagerwerte[4];
    float  Winkel;             //Nur bei Schräglager
    int Fest_Lose;          //1 = Fest, 0 = Lose
    int Schraeg_Grade;      //1 = Schraeg 0 = Grade
    struct sLager *Next;
}TLager;

extern int LagerCounter;
extern int TrapezCounter;
extern int RechteckCounter;
extern int AeussMomentCounter;
extern int PunktCounter;
extern TLager        *FirstLager;
extern TTrapezlast   *FirstTrapez;
extern TRechtecklast *FirstRechteck;
extern TRechtecklast *LastRechteck;
extern TPunktlast    *FirstPunkt;
extern TPunktlast    *LastPunkt;
extern TAeussMoment  *FirstAeussMoment;

//#endif // DATASTRUCTURE_H_INCLUDED



//#ifndef TEAMS_H_INCLUDED
//#define TEAMS_H_INCLUDED
//#include "datastructure.h"

void askLager(TLager **);
void askRechteck(TRechtecklast **);
void askTrapez(TTrapezlast **);
void askPunktlast(TPunktlast **);
void askAeussMoment(TAeussMoment **);
void calcLager();

//#endif // TEAMS_H_INCLUDED



//#ifndef FUNKTION_H_INCLUDED
//#define FUNKTION_H_INCLUDED

	//#include "datastructure.h"

void clearBuffer();
void clearScreen();
void waitForEnter();
void printLine(char c, int n);
int getText(char* toprint, int maximal, int isLeer, char** Text);
int getNumber(char* toprint, int* Number, int min, int max);
void LeertastenLoesschen(char *);
int askAgain();
	//void freeMannschaft(TTeam *);

//#endif
