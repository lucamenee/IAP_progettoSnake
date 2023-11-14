//895383

/**
 * @file main.c
 * @author Luca Meneghetti
 * @mainpage Snake labyrinth
 * @brief Progetto snake interattivo e autorisolvente
 * @date 30/01/2023
 *
 * @section intro Introduzione
 *Questo programma permette di leggere leggere in input un labirinto, e poi si puo' scegliere se farlo risolvere in automatico dal programma o se iniziare a giocarci.
 *
 * @section input Lettura input
 *Vengono chieste le dimensioni del labirinto e, inserendo riga per riga, l'algoritmo legge in input dall'utente il labirinto
 *
 * @section ai Modalita' autosolve
 *Viene chiesto all'utente se volglia che il labirinto si risolva da solo o se voglia giocarci lui. Nel primo caso viene fatta partire la modalita' autosolve, che si compone dei seguenti passaggi:
 *
 * @subsection loop1 Ciclo esterno
 *In questo ciclo while, per 4 secondi, il programma prova a risolvere il maggior numero di volte il labirinto, tenendo alla fine di tutto la seqeunza di mosse che che gli hanno permesso di arrivare alla fine con il punteggio maggiore.
 *
 * @subsection loop2 Ciclo interno
 *Il while piu' interno, invece si occupa della risoluzione del singolo labirinto, il funzionamento alla sua base e' estremamente semplice.
 * Ad ogni ciclo, si controlla se lo snake e' distante solo una mossa dall'uscita.
 * Se si, allora allora si esegue tale mossa mossa, altrimenti, vine scelta una mossa casuale tra nord , sud, est ed ovest; dopodiche' viene controllato che questa mossa sia valida, se non lo e' lo snake torna nella posizione precedente e nulla viene modificato, altrimenti, la posizione viene modificata e il punteggio parziale viene modificato.
 * Per ottimizzare il percorso, non e' possibile che lo snake ritorni sui suoi passi (cosi' facendo questa modalita' rispetta la regola della cosa dello snake),
 * Questo while termina in solo 3 occasioni: se viene raggiunta la fine, se la testa dello snake e' circondata solo da caselle in sui e' gia' stata o in cui non e' permesso andarci, o se la risoluzione ha richiesto piu' di un secondo per essere terminata.
 *
 * @subsection out Output
 *Questa modalita' genera come output la sequanza di mosse che ha permesso si arrivare all'uscita con il punteggio piu' alto, e il punteggio corrispondente.
 *
 * @section interattiva Modalita' interattiva
 *Se, invece, viene scelta la modalita' interattiva, all'utente verra' chiesto di spostarsi inserendo in input i seguenti caratteri N, S, E, O.
 * Ad ogni mossa il punteggio viene aggiornato, e il programma non termina finche' non viene raggiunta l'uscita.
 * Infine viene stampata a video la sequenza completa delle mosse valide usate, e il punteggio finale.
 * In questa modalita' non si tiene conto della coda dello snake.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include "functions.h"




int main(int argc, char *argv[])
{

    int colonne, righe;
    int xInizio, yInizio, xFine, yFine;
    bool trovatoInizio = false, trovatoFine = false;


    // leggo in input il labirinto e le sue dimensioni
    int unused;

    do {
        unused = scanf("%i", &colonne);
    } while (colonne < 3);
    do {
        unused = scanf("%i", &righe);
    } while (righe < 3);
    getchar();

    char lab[righe][colonne], labProv[righe][colonne];
    char strRiga[colonne];

    for (int i = 0; i < righe; i++) {
        unused = scanf("%[^\n]s \n", strRiga);
        for (int j = 0; j < colonne; j++) {
            lab[i][j] = strRiga[j];
            labProv[i][j] = strRiga[j];
            if (lab[i][j] == 'o' && !trovatoInizio) {
                xInizio = j;
                yInizio = i;
                trovatoInizio = true;
            } else if (lab[i][j] == '_' && !trovatoFine) {
                xFine = j;
                yFine = i;
                trovatoFine = true;
            }
        }
        getchar();
    }



    char nextMove[2], mosse[colonne * righe];
    int xPrec, yPrec, punteggio = 1000;
    int countTrapani = 0;


    bool cond = false;
    if (argc > 1 && !strcmp(*(argv + 1), "--challenge"))
        cond = true;

    char autosolve;
    if (!cond) {
        printf("autosolve?[Y/n] \n");
        unused = scanf("%c", &autosolve);
    }


    if (cond || autosolve == 'Y' || autosolve == 'y') {     //ciclo esterno

        int random, xStart = xInizio, yStart = yInizio, bestPunteggio = 0;
        char best[colonne * righe];

        float timeStart = clock()/CLOCKS_PER_SEC, timeStartCiclo;

        while (clock()/CLOCKS_PER_SEC - timeStart < 3) { // ciclo interno
            // setto variabili modificate a valore di base
            punteggio = 1000;
            strcpy(mosse, "");
            xInizio = xStart;
            yInizio = yStart;
            countTrapani = 0;
            for (int i = 0; i < righe; i++) {// ripristino il labirrinto allo stato iniziale
                for (int j = 0; j < colonne; j++) {
                    lab[i][j] = labProv[i][j];
                }
            }


            timeStartCiclo = clock()/CLOCKS_PER_SEC;
            do {
                xPrec = xInizio;
                yPrec = yInizio;

                //controllo se sono a una mossa di distanza dall'uscita
                if (yInizio > 0 && lab[yInizio-1][xInizio] == '_') {
                     strcpy(nextMove, "N");
                     yInizio--;
                     strcat(mosse, nextMove);
                } else if (yInizio < righe - 1 && lab[yInizio+1][xInizio] == '_') {
                     strcpy(nextMove, "S");
                     yInizio++;
                     strcat(mosse, nextMove);
                } else if (xInizio > 0 && lab[yInizio][xInizio-1] == '_') {
                     strcpy(nextMove, "O");
                     xInizio--;
                     strcat(mosse, nextMove);
                } else if (xInizio < colonne - 1 && lab[yInizio][xInizio+1] == '_') {
                     strcpy(nextMove, "E");
                     xInizio++;
                     strcat(mosse, nextMove);
                } else {




                    random = rand() % 4;
                    if (random == 0) {
                        strcpy(nextMove, "N");
                        yInizio--;
                    } else if (random == 1) {
                        strcpy(nextMove, "S");
                        yInizio++;
                    } else if (random == 2) {
                        strcpy(nextMove, "E");
                        xInizio++;
                    } else {
                        strcpy(nextMove, "O");
                        xInizio--;
                    }

                if ((lab[yInizio][xInizio] == '#' && !countTrapani) || xInizio <= 0 || yInizio <= 0 || xInizio >= colonne -1 || yInizio >= colonne -1 || lab[yInizio][xInizio] == '.') {
                    xInizio = xPrec;
                    yInizio = yPrec;

                } else {
                    strcat(mosse, nextMove);
                    punteggio--;

                    if (lab[yInizio][xInizio] == '$') {
                        punteggio += 10;
                    } else if (lab[yInizio][xInizio] == '!') {
                        punteggio /= 2;
                    } else if (lab[yInizio][xInizio] == 'T') {
                        countTrapani += 3;
                    } else if (lab[yInizio][xInizio] == '#') {
                        countTrapani--;
                    }

                    lab[yPrec][xPrec] = '.';
                    lab[yInizio][xInizio] = 'o';
                }
            }
            } while ((!((xInizio == xFine) && (yInizio == yFine)) && !isCieco(xInizio, yInizio, *lab, righe, colonne)) && !(clock()/CLOCKS_PER_SEC - timeStartCiclo > 1));

            if (punteggio > bestPunteggio && xInizio == xFine && yInizio == yFine) {
                strcpy(best, mosse);
                bestPunteggio = punteggio;
            }

        }

        int t = 0;
        while (best[t] != '\0') {
            printf("%c", best[t++]);
        }
        printf("\n");

        if (!cond) printf("%i \n", bestPunteggio);



    } else {        //parte interattiva

        printf("game started. Write N, S, E, O for moving \n");

        strcpy(mosse, "");
        char input;


        do {
            xPrec = xInizio;
            yPrec = yInizio;
            lab[yInizio][xInizio] = ' ';
            do {
                unused = scanf("%c", &input);
            } while (!(input == 'N' || input == 'S' || input == 'E' || input == 'O'));

            if (input == 'N') {yInizio--;}
            if (input == 'S') {yInizio++;}
            if (input == 'E') {xInizio++;}
            if (input == 'O') {xInizio--;}



            if ((lab[yInizio][xInizio] == '#' && !countTrapani) || xInizio < 0 || yInizio < 0 || xInizio >= colonne || yInizio >= colonne) {
                xInizio = xPrec;
                yInizio = yPrec;
                printf("mossa non valida\n");
            } else {

                strncat(mosse, &input, 1);
                punteggio--;

                // controllo se sono sopra a un "oggetto speciale"
                if (lab[yInizio][xInizio] == '$') {
                    punteggio += 10;
                } else if (lab[yInizio][xInizio] == '!') {
                    punteggio /= 2;
                } else if (lab[yInizio][xInizio] == '#') {
                    countTrapani--;
                } else if (lab[yInizio][xInizio] == 'T') {
                    countTrapani += 3;
                }

                lab[yInizio][xInizio] = 'o';
                printLab(*lab, righe, colonne);
            }

        } while (!((xInizio == xFine) && (yInizio == yFine)));

        printLab(*lab, righe, colonne);
        printf("%i\n", punteggio);
        printf("%s\n", mosse);
    }

    return 0;
}



