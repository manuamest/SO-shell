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
    char line[1024];
    char* trozos[128];
    int nTrozos;
    tList L;
    createEmptyList(&L);
    datos* data;
    data->list = &L;
    data->cmdNumber = 0;
    data->finished = (bool *) true;
    while (data->finished) {
        //prints a promt
        printPrompt();
        readEntry(line, &L, data->cmdNumber);
        nTrozos = TrocearCadena(line, trozos);
        //analizar
        execute(trozos, nTrozos, data);
    }
    clearOutList(&L);
    free(L);
}