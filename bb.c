#include <stdio.h>
#include <stdlib.h>
#include "bb.h"
#include <math.h>
#define PI 3.14159265
#include <string.h>

int LagerCounter       = 0;
int RechteckCounter    = 0;
int TrapezCounter      = 0;
int PunktCounter       = 0;
int AeussMomentCounter = 0;

TLager        *FirstLager       = NULL;
TPunktlast    *FirstPunkt       = NULL;
TTrapezlast   *FirstTrapez      = NULL;
TRechtecklast *FirstRechteck    = NULL;
TRechtecklast *LastRechteck     = NULL;
TAeussMoment  *FirstAeussMoment = NULL;

/********************************************************/
/* void clearbuffer					*/
/* Funktion:  löscht den tastaturpuffer			*/
/* ******************************************************/
void clearBuffer()
{
    char Dummy;
    do
	scanf("%c", &Dummy);
    while(Dummy != '\n');
}

/********************************************************/
/* void printline					*/
/* Funktion:  schreibt ein zeichen in eine zeile	*/
/* Parameter: -Zeichen das geschrieben werden soll	*/
/*            -Wieoft das Zeichen geschriebenwird	*/
/********************************************************/
void printLine(char Zeichen, int Anzahl)
{
    int i = 0;
    for (i = 0; i < Anzahl; i++)
        printf("%c", Zeichen);
    printf("\n\n");
}

/********************************************************/
/* void clearScreen					*/
/* Funktion:  löscht das Bildschrim			*/
/* ******************************************************/
void clearScreen()
{
    system("clear");
}

/********************************************************/
/* void waitForEnter					*/
/* Funktion:  bittet und wartet auf eingabe eines Enter	*/
/********************************************************/
void waitForEnter()
{
    printf("\nBitte Eingabetaste druecken ...");
    clearBuffer();
}

/********************************************************/
/* int askAgain()					*/
/* Funktion:  Ja/Nein Abfrage				*/
/********************************************************/
int askAgain()
{
    char JaNein;
    int Erg;

    do
    {
	scanf("%c", &JaNein);
	if (JaNein != '\n')
	    clearBuffer();
	// Ist Eingabe richtig?
	if(JaNein != 'j' && JaNein != 'J' && JaNein != 'n' && JaNein != 'N')
	    printf("\nFalsche Eingabe! Verwenden Sie bitte nur 'j' oder 'n'!\n");
	}
    while (JaNein != 'j' && JaNein != 'J' && JaNein != 'n' && JaNein != 'N');

    if (JaNein == 'j' || JaNein == 'J')
	Erg = 1;
    else    // Bei 'n' oder 'N'
	Erg = 0;
    return Erg;
}

/********************************************************/
/* void askLager					*/
/* Funktion:  Fügt Lagerkräfte hinzu			*/
/* ******************************************************/
void askLager(TLager **NEU)
{
    int isWeiter = 0;
    if (*NEU)
        free(*NEU);
    (*NEU) = malloc(sizeof(TLager));

    do
    {
        printf("Ist die Lagerkraft Fest(1) oder Lose(0)?\n -> ");
        scanf("%i", &(*NEU)->Fest_Lose);
        clearBuffer();
    }
    while (((*NEU)->Fest_Lose<0) || ((*NEU)->Fest_Lose>1));

    do
    {
        printf("Ist die Lagerkraft Schraeg(1) oder Gerade(0)?\n -> ");
        scanf("%i", &(*NEU)->Schraeg_Grade);
        clearBuffer();
        if((*NEU)->Schraeg_Grade == 1)
        {
            do
            {
                printf("Wie ist der Winkel?\n -> ");
                isWeiter=scanf("%f", &(*NEU)->Winkel);
                clearBuffer();

            }
	    while (isWeiter != 1);
        }
    }
    while (((*NEU)->Schraeg_Grade > 1) || ((*NEU)->Schraeg_Grade < 0));

    do
    {
        printf("Was ist die Position von der Lagerkraft?\n -> ");
        isWeiter=scanf("%f", &(*NEU)->Position);
        clearBuffer();
    }
    while (isWeiter != 1);

    (*NEU)->Next = NULL;
    LagerCounter++;
    //printf("%i    %i    %f\n", (*NEU)->Fest_Lose, (*NEU)->Schraeg_Grade, (*NEU)->Position);
    printf("Moechten Sie eine weitere Lagerkraft eingeben?\n -> ");
        isWeiter = askAgain();
        if (isWeiter == 1)
            askLager(&((*NEU)->Next));
}

/********************************************************/
/* void askRechteck					*/
/* Funktion:  Fügt Rechtecklasten hinzu			*/
/* ******************************************************/
void askRechteck(TRechtecklast **NEU)
{
    int isWeiter = 0;
    if (*NEU)
        free(*NEU);
    (*NEU) = malloc(sizeof(TRechtecklast));
    (*NEU)->Next = NULL;

    do
    {
        printf("Wie ist die Position (X1)?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Position_X1);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("Wie ist die Laenge?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Laenge);
        clearBuffer();
    }
    while (isWeiter != 1);
    (*NEU)->Position_Last = (*NEU)->Position_X1 + (*NEU)->Laenge / 2;
    //printf("\nPosition_Last: %f\n", (*NEU)->Position_Last);;

    do
    {
        printf("Wie ist die Hoehe?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Hoehe);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("In welche Richtung geht die Last? Uhrzeiger(0) oder gegen Uhrzeiger(1)?\n -> ");
        scanf("%i", &(*NEU)->Richtung);
        clearBuffer();
    }
    while (((*NEU)->Richtung<0) || ((*NEU)->Richtung>1));

    (*NEU)->Flaechenlast = (*NEU)->Laenge * (*NEU)->Hoehe;
    LastRechteck = (*NEU);
    RechteckCounter++;

    printf("Moechten Sie eine weitere Rechtecklast eingeben?\n -> ");
        isWeiter = askAgain();
        if (isWeiter == 1)
            askRechteck(&((*NEU)->Next));
}

/********************************************************/
/* void askTrapez					*/
/* Funktion:  Fügt Trapezlasten hinzu			*/
/********************************************************/
void askTrapez(TTrapezlast **NEU)
{
    int isWeiter = 0;
    if (*NEU)
    	free(*NEU);
    (*NEU) = malloc(sizeof(TTrapezlast));
    (*NEU)->Next = NULL;

    do
    {
        printf("Wie ist die Position (X1)?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Position_X1);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("Wie ist die Position (X2)?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Position_X2);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("Wie ist die Hoehe X1?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Hoehe_X1);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("Wie ist die Hoehe X2?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Hoehe_X2);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("In welche Richtung geht die Last? Uhrzeiger(0) oder gegen Uhrzeiger(1)?\n -> ");
        scanf("%i", &(*NEU)->Richtung);
        clearBuffer();
    }
    while (((*NEU)->Richtung<0) || ((*NEU)->Richtung>1));

    (*NEU)->Laenge = abs((*NEU)->Position_X2 - (*NEU)->Position_X1);
    if(((*NEU)->Position_X1 != 0) && ((*NEU)->Position_X2 != 0))
    {
        TRechtecklast *RechtecklastNEU = NULL;
        if (RechtecklastNEU)
            free(RechtecklastNEU);
        RechtecklastNEU = malloc(sizeof(TRechtecklast));
        RechtecklastNEU->Position_X1 = (*NEU)->Position_X1;
        RechtecklastNEU->Laenge = (*NEU)->Laenge;
        if((*NEU)->Hoehe_X1 < (*NEU)->Hoehe_X2)
            RechtecklastNEU->Hoehe = (*NEU)->Hoehe_X1;
        else
            RechtecklastNEU->Hoehe = (*NEU)->Hoehe_X2;
        RechtecklastNEU->Position_Last = RechtecklastNEU->Position_X1 + (RechtecklastNEU->Laenge / 2);
	//printf("\nPosition_Rechtecklast im Trapez: %f\n",RechtecklastNEU->Position_Last);
        RechtecklastNEU->Richtung = (*NEU)->Richtung;
        RechtecklastNEU->Flaechenlast = RechtecklastNEU->Laenge * RechtecklastNEU->Hoehe;
        if(RechteckCounter == 0)
            FirstRechteck = LastRechteck = RechtecklastNEU;
        else
	    LastRechteck->Next = RechtecklastNEU;
        RechteckCounter++;
    }
    if((*NEU)->Hoehe_X1 < (*NEU)->Hoehe_X2)
        (*NEU)->Position_Last = (*NEU)->Position_X1 + ((*NEU)->Laenge * 2 / 3);
    else
        (*NEU)->Position_Last = (*NEU)->Position_X1 + ((*NEU)->Laenge / 3);
    (*NEU)->HoeheDreieck = abs((*NEU)->Hoehe_X2 - (*NEU)->Hoehe_X1);
    (*NEU)->Dreieckflaeche = (*NEU)->HoeheDreieck * ((*NEU)->Laenge / 2);
    TrapezCounter++;
    printf("Moechten Sie eine weitere Trapezlasts eingeben?\n -> ");
        isWeiter = askAgain();
        if (isWeiter == 1)
            askTrapez(&((*NEU)->Next));
}

/********************************************************/
/* void askPunktlast					*/
/* Funktion:  Fügt Punktlasten hinzu			*/
/* ******************************************************/
void askPunktlast(TPunktlast **NEU)
{
    int isWeiter = 0;
    if (*NEU)
        free(*NEU);
    (*NEU) = malloc(sizeof(TPunktlast));
    (*NEU)->Next = NULL;

    do
    {
        printf("Wie ist die Position?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Position);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("Wie ist die Last?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Last);
        clearBuffer();
    }
    while (isWeiter != 1);

    do
    {
        printf("In welche Richtung geht die Last? Uhrzeiger(0) oder gegen Uhrzeiger(1)?\n -> ");
        scanf("%i", &(*NEU)->Richtung);
        clearBuffer();
    }
    while (((*NEU)->Richtung<0) || ((*NEU)->Richtung>1));

    PunktCounter++;
    printf("Moechten Sie eine weitere Punktlasts eingeben?\n -> ");
        isWeiter = askAgain();
        if (isWeiter == 1)
            askPunktlast(&((*NEU)->Next));
}

/********************************************************/
/* void askAuessMoment					*/
/* Funktion:  Fügt AeussMoment hinzu			*/
/********************************************************/
void askAeussMoment(TAeussMoment **NEU)
{
    int isWeiter = 0;

    if (*NEU)
        free(*NEU);
    (*NEU) = malloc(sizeof(TAeussMoment));
    (*NEU)->Next = NULL;

    do
    {
        printf("Wie ist die Last?\n -> ");
        isWeiter = scanf("%f", &(*NEU)->Last);
        clearBuffer();
    }while (isWeiter != 1);


    do
    {
        printf("In welche Richtung geht der Aeussere Moment? Uhrzeiger(0) oder gegen Uhrzeiger(1)?\n -> ");
        scanf("%i", &(*NEU)->Richtung);
        clearBuffer();
    }while (((*NEU)->Richtung<0) || ((*NEU)->Richtung>1));

    AeussMomentCounter++;
    printf("Moechten Sie einen weiteren Aeusseren Moment eingeben?\n -> ");
        isWeiter = askAgain();
        if (isWeiter == 1)
            askAeussMoment(&((*NEU)->Next));
}

/********************************************************/
/*void calcLager					*/
/*Funktion:  Berechnet die Lagerkräfte			*/
/********************************************************/
void calcLager()
{
    int i;
    double TempErgebnis = 0.0;
    TAeussMoment *TempAuessMoment = FirstAeussMoment;
    TRechtecklast  *TempRechteck = FirstRechteck;
    TTrapezlast *TempTrapez = FirstTrapez;
    TPunktlast *TempPunkt = FirstPunkt;
    TLager ** Lager = &FirstLager;

    (*Lager)->Lagerwerte[0] = 0.0;
    (*Lager)->Lagerwerte[1] = 0.0;
    (*Lager)->Lagerwerte[2] = 0.0;
    (*Lager)->Next->Lagerwerte[0] = 0.0;
    (*Lager)->Next->Lagerwerte[1] = 0.0;
    (*Lager)->Next->Lagerwerte[2] = 0.0;

// Berechnung von BY
    for(i=0; i<AeussMomentCounter; i++)
    {
	// printf("\n\nAuessMoment\nMoment: %f   Richtung: %i\nTempErgebnis vorher = %f",TempAuessMoment->Last,
	// 	   TempAuessMoment->Richtung ,TempErgebnis);
        if(TempAuessMoment->Richtung == 1)
            TempErgebnis -= TempAuessMoment->Last;
        else
            TempErgebnis += TempAuessMoment->Last;
	// printf("\naeTempErgebnis nachher = %f",TempErgebnis);
        TempAuessMoment = TempAuessMoment->Next;
    }

    for(i=0; i<PunktCounter; i++)
    {
	// printf("\n\nPunkt\nPosition:%f   Last:%f   Richtung:%i\nTempErgebnis vorher = %f",TempPunkt->Position,
	//	   TempPunkt->Last, TempPunkt->Richtung,TempErgebnis);
        if(TempPunkt->Position > (*Lager)->Position)
        {
            if(TempPunkt->Richtung == 1)
                TempErgebnis += TempPunkt->Last*(TempPunkt->Position - (*Lager)->Position);

            else
                TempErgebnis -= TempPunkt->Last*(TempPunkt->Position - (*Lager)->Position); // +=
        }
        else
        {
            if(TempPunkt->Richtung == 1)
                TempErgebnis += TempPunkt->Last*(*Lager)->Position;// - TempPunkt->Position);
            else
                TempErgebnis -= TempPunkt->Last*((*Lager)->Position - TempPunkt->Position);
        }
        TempPunkt = TempPunkt->Next;
	// printf("\nptTempErgebnis nachher = %f",TempErgebnis);
    }

    for(i=0; i<RechteckCounter; i++)
    {
	// printf("\n\nRechteck\nPosition_Last:%f   Fleachenast:%f   Richtung:%i\nTempErgebnis vorher = %f",
	//	   TempRechteck->Position_Last, TempRechteck->Flaechenlast, TempRechteck->Richtung,TempErgebnis);
        if(TempRechteck->Position_Last > (*Lager)->Position)
        {
            if(TempRechteck->Richtung == 1)
                TempErgebnis += TempRechteck->Flaechenlast*TempRechteck->Position_Last;// - (*Lager)->Position);
            else
                TempErgebnis -= TempRechteck->Flaechenlast*TempRechteck->Position_Last;// - (*Lager)->Position);
        }
        else
        {
            if(TempRechteck->Richtung == 1)
                TempErgebnis += TempRechteck->Flaechenlast*((*Lager)->Position - TempRechteck->Position_Last);
            else
                TempErgebnis -= TempRechteck->Flaechenlast*((*Lager)->Position - TempRechteck->Position_Last * 2);
        }
        TempRechteck = TempRechteck->Next;
	// printf("\nreTempErgebnis nachher = %f",TempErgebnis);
    }
 
    for(i=0; i<TrapezCounter; i++)
    {
	// printf("\n\nTrapez\nPosition_Last:%f   Last_Dreieck:%f   Richtung:%i\nTempErgebnis vorher = %f",
	//	   TempTrapez->Position_Last, TempTrapez->Dreieckflaeche, TempTrapez->Richtung, TempErgebnis);
        if(TempTrapez->Position_Last > (*Lager)->Position)
        {
            if(TempTrapez->Richtung == 1)
                TempErgebnis += TempTrapez->Dreieckflaeche*TempTrapez->Position_Last;// - (*Lager)->Position);
            else
                TempErgebnis -= TempTrapez->Dreieckflaeche*TempTrapez->Position_Last;// - (*Lager)->Position);
        }
        else
        {
            if(TempTrapez->Richtung == 1)
                TempErgebnis += TempTrapez->Dreieckflaeche*((*Lager)->Position - TempTrapez->Position_Last);
            else
                TempErgebnis -= TempTrapez->Dreieckflaeche*((*Lager)->Position - TempTrapez->Position_Last);
        }
        TempTrapez = TempTrapez->Next;
	// printf("\ntrTempErgebnis nachher = %f",TempErgebnis);
    }

    if((*Lager)->Position < (*Lager)->Next->Position)
        TempErgebnis /= ((*Lager)->Position) - (*Lager)->Next->Position;
    else
        TempErgebnis /= ((*Lager)->Next->Position) - (*Lager)->Position;
	(*Lager)->Next->Lagerwerte[1] = TempErgebnis;
	// printf("\nBy= %f",(*Lager)->Next->Lagerwerte[1]);

// Berechnung von AY
    TempErgebnis = 0.0;
    TempAuessMoment = FirstAeussMoment;
    TempRechteck = FirstRechteck;
    TempTrapez = FirstTrapez;
    TempPunkt = FirstPunkt;
    for(i=0; i<PunktCounter; i++)
    {
        if(TempPunkt->Richtung == 1)
	    TempErgebnis += TempPunkt->Last;
        else
	    TempErgebnis -= TempPunkt->Last;
        TempPunkt = TempPunkt->Next;
	// printf("\nTempErgebnis nachher = %f",TempErgebnis);
    }

    for(i=0; i<RechteckCounter; i++)
    {
        if(TempRechteck->Richtung == 1)
            TempErgebnis -= TempRechteck->Flaechenlast;
        else
            TempErgebnis += TempRechteck->Flaechenlast;
        TempRechteck = TempRechteck->Next;
	// printf("\nTempErgebnis nachher = %f",TempErgebnis);
    }

    for(i=0; i<TrapezCounter; i++)
    {
        if(TempTrapez->Richtung == 1)
            TempErgebnis -= TempTrapez->Dreieckflaeche;
        else
            TempErgebnis += TempTrapez->Dreieckflaeche;
        TempTrapez = TempTrapez->Next;
	// printf("\nTempErgebnis nachher = %f",TempErgebnis);
    }
    TempErgebnis -= (*Lager)->Next->Lagerwerte[1];
    (*Lager)->Lagerwerte[1] = TempErgebnis;
	// printf("\nAy: %f",(*Lager)->Lagerwerte[1]);

// AX Berechnung
    TempErgebnis = 0.0;

    if((*Lager)->Schraeg_Grade == 1)
    {
        TempErgebnis = tan((90 - (*Lager)->Winkel)/180*PI);
        TempErgebnis = (*Lager)->Lagerwerte[1] / TempErgebnis;
        if(TempErgebnis < 0) TempErgebnis *= -1;
	(*Lager)->Lagerwerte[0] = TempErgebnis;
    }
	// printf("\nAx: %f",(*Lager)->Lagerwerte[0]);
    (*Lager)->Next->Lagerwerte[0] = (*Lager)->Lagerwerte[0];
    (*Lager)->Lagerwerte[2] = (*Lager)->Lagerwerte[1]/sin((60 * PI) / 180);
    if((*Lager)->Lagerwerte[2] < 0) (*Lager)->Lagerwerte[2] *= -1;

}
/*************************############# main #############*************************/
int main()
{
    TLager *TempLager;
    TempLager = FirstLager;
    int i = 0;
// Informationsabfrage
    printf("***************  Lagerkraft  ***************\n\n");
	askLager(&FirstLager);

    clearScreen();
    printf("****************  Punktlast  ***************\n\n");
    printf("Moechten Sie eine Punktlast eingeben?\n -> ");
    i = askAgain();
    if (i == 1)
	askPunktlast(&FirstPunkt);

    clearScreen();
    printf("**************  Rechteckslast  *************\n\n");
    printf("Moechten Sie eine Rechteckslast eingeben?\n -> ");
    i = askAgain();
    if (i == 1)
	askRechteck(&FirstRechteck);

    clearScreen();
    printf("***************  Trapezlast  ***************\n\n");
    printf("Moechten Sie eine Trapezlast eingeben?\n -> ");
    i = askAgain();
    if (i == 1)
	askTrapez(&FirstTrapez);

    clearScreen();
    printf("*************  Aeusserer Moment  ***********\n\n");
    printf("Moechten Sie einen Auesseren Moment eingeben?\n -> ");
    i = askAgain();
    if (i == 1)
	askAeussMoment(&FirstAeussMoment);

    calcLager();

    clearScreen();
    TempLager = FirstLager;

    for(i=0;i<LagerCounter; i++)
    {
        printf("\nLager Nr.%i\nAx : %f\nAy :%f\n",i+1, TempLager->Lagerwerte[0], TempLager->Lagerwerte[1]);
        if(TempLager->Schraeg_Grade == 1)
            printf("A : %f\n",TempLager->Lagerwerte[2]);
        TempLager = TempLager->Next;
    }

    waitForEnter();
    return 0;
}
