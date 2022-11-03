/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "commands.h"


void printPrompt() {
    printf("#$ ");
}

void toHist(char* line, datos* data) {
    tItemL d;
    strcpy(d.command, line);
    d.number = data->cmdNumber;
    insertItem(d, &data->list);
    data->cmdNumber++;
}

void readEntry(char* line, datos* data) {
    if(fgets(line, 1024, stdin)) {
        toHist(line, data);
    } else {
        printf("ERROR: No se puede leer el input\n");
    }
}

int main() {
    char line[1024];
    char* trozos[128];
    int nTrozos;
    tList lista;
    createEmptyList(&lista);
    datos data = { lista, false, 0 };

    while (!data.finished) {
        //prints a promt
        printPrompt();
        readEntry(line, &data);
        nTrozos = TrocearCadena(line, trozos);
        //analizar
        execute(trozos, nTrozos, &data);
    }
    clearOutList(&data.list);
    free(data.list);
}