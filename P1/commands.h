/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <grp.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include "list.h"
#ifndef SOP0_COMMANDS_H
#define SOP0_COMMANDS_H

/*
typedef struct _cmdEntry
{
    char *name;
    int(*function)(int argc, char *argv[]);
    char *ayuda;
} cmdEntry;
*/

void processCmd(bool* finished, char* trozos[], tList *L, int* cmdNumber, int nTrozos);
void cmdError();
void cmdAutores(char* opcion);
void cmdPid(char* opcion);
void cmdCarpeta(char* opcion);
void cmdFecha(char* opcion);
void cmdHist(tList *L, char* opcion, int* cmdNumber);
void cmdComando(char* opcion, bool* finished, char* trozos[], tList *L, int* cmdNumber, int nTrozos);
void cmdInfosis();
void cmdAyuda(char* opcion);
void cmdStat(char* opcion);
void cmdExit(bool* finished,const char* opcion, tList *L);
int TrocearCadena(char* cadena, char* trozos[]);

#endif //SOP0_COMMANDS_H

