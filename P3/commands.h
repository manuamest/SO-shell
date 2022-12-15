/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <grp.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <pwd.h>
#include "list.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/resource.h>
#ifndef SOP0_COMMANDS_H
#define SOP0_COMMANDS_H
#define NCOMMANDS 32
#define MAXVAR 1024

typedef struct entvars {
    void* var[4096];
    int lastPos;
}entvars;

typedef struct datos{
    tList list;
    tList memoryList;
    tList processList;
    bool finished;
    int cmdNumber;
    char** arg3;
    struct entvars entvar;
}datos;

struct cmdEntry{
    char *name;
    int(*function)(char *argv[], int argc, datos* data);
    char *ayuda;
};

extern struct cmdEntry cmdTable[];
int execute(char* trozos[], int nTrozos, datos* data);
int cmdAutores(char* opcion[], int nTrozos, datos* data);
int cmdPid(char* opcion[], int nTrozos, datos* data);
int cmdCarpeta(char* opcion[], int nTrozos, datos* data);
int cmdFecha(char* opcion[], int nTrozos, datos* data);
int cmdHist(char* opcion[], int nTrozos, datos* data);
int cmdComando(char* opcion[], int nTrozos, datos* data);
int cmdInfosis(char* opcion[], int nTrozos, datos* data);
int cmdAyuda(char* opcion[], int nTrozos, datos* data);
int cmdExit(char* opcion[], int nTrozos, datos* data);
int TrocearCadena(char* cadena, char* trozos[]);
int cmdCreate(char* opcion[], int nTrozos, datos* data);
int cmdStat(char* opcion[], int nTrozos, datos* data);
int cmdList(char* opcion[], int nTrozos, datos* data);
int cmdDelete(char* opcion[], int nTrozos, datos* data1);
int cmdDeltree(char* opcion[], int nTrozos, datos* data);
int cmdAllocate(char* opcion[], int nTrozos, datos* data);
int cmdDeallocate(char* opcion[], int nTrozos, datos* data);
int cmdio(char* opcion[], int nTrozos, datos* data);
int cmdMemdump(char* opcion[], int nTrozos, datos* data);
int cmdMemfill(char* opcion[], int nTrozos, datos* data);
int cmdMemory(char* opcion[], int nTrozos, datos* data);
int cmdRecurse(char* opcion[], int nTrozos, datos* data);
int cmdPriority(char* opcion[], int nTrozos, datos* data);
int cmdShowvar(char* opcion[], int nTrozos, datos* data);
int cmdChangevar(char* opcion[], int nTrozos, datos* data);
int cmdShowenv(char* opcion[], int nTrozos, datos* data);
int cmdFork(char* opcion[], int nTrozos, datos* data);
int cmdExecute(char* opcion[], int nTrozos, datos* data);
int cmdListjobs(char* opcion[], int nTrozos, datos* data);
int cmdDeljobs(char* opcion[], int nTrozos, datos* data);
int cmdJob(char* opcion[], int nTrozos, datos* data);

#endif //SOP0_COMMANDS_H
