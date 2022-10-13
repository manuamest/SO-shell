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
typedef struct datos{
    tList list;
    bool finished;
    int cmdNumber;
}datos;
struct cmdEntry{
    char *name;
    void(*function)(char *argv[], int argc, datos* data);
    char *ayuda;
};
extern struct cmdEntry cmdTable[];
int execute(char* trozos[], int nTrozos, datos* data);
//void processCmd(bool* finished, char* trozos[], tList *L, int* cmdNumber, int nTrozos);
void cmdError();
void cmdAutores(char* opcion[], int nTrozos, datos* data);
void cmdPid(char* opcion[], int nTrozos, datos* data);
void cmdCarpeta(char* opcion[], int nTrozos, datos* data);
void cmdFecha(char* opcion[], int nTrozos, datos* data);
void cmdHist(char* opcion[], int nTrozos, datos* data);
void cmdComando(char* opcion[], int nTrozos, datos* data);
void cmdInfosis(char* opcion[], int nTrozos, datos* data);
void cmdAyuda(char* opcion[], int nTrozos, datos* data);
void cmdCreate(char* opcion[], int nTrozos, datos* data);
void cmdStat(char* opcion[], int nTrozos, datos* data);
void cmdList(char* opcion[], int nTrozos, datos* data);
void cmdDelete(char* opcion[], int nTrozos, datos* data1);
void cmdDeltree(char* opcion[], int nTrozos, datos* data);
void cmdExit(char* opcion[], int nTrozos, datos* data);
int TrocearCadena(char* cadena, char* trozos[]);

#endif //SOP0_COMMANDS_H
