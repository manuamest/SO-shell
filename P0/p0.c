/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "commands.h"

void printPrompt() {
    printf("#$");
}

void toHist(tList *L, char* line, int* cmdNumber) {
    tItemL d;
    strcpy(d.command, line);
    d.number = *cmdNumber;
    insertItem(d, LNULL, L);
    (*cmdNumber)++;
}

void readEntry(char* line, tList *L, int* cmdNumber) {
    if(fgets(line, 1024, stdin)) {
        toHist(L, line, cmdNumber);
    } else {
        printf("ERROR: No se puede leer el input\n");
    }
}

int main() {

    bool finished = false;
    char line[1024];
    char* trozos[128];
    int* cmdNumber = malloc(sizeof (int));
    *cmdNumber = 0;
    tList L;
    int nTrozos;
    createEmptyList(&L);
    while (!finished) {
        //prints a promt
        printPrompt();
        readEntry(line, &L, cmdNumber);
        nTrozos = TrocearCadena(line, trozos);
        //analizar
        processCmd(&finished, trozos, &L, cmdNumber, nTrozos);
    }
    free(cmdNumber);
    clearOutList(&L);
    free(L);
}