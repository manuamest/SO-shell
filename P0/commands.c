/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */
#include "commands.h"

/*
cmdEntry cmdTable[] = {
        {"autores", cmdAutores,"uso: autores [-n|-l]\tMuestra los nombres y logins de los autores\n"},
        {"pid", cmdPid, "uso: pid [-p]\tMuestra el pid del shell o de su proceso padre\n"},
        {"carpeta", cmdCarpeta, "uso: carpeta [dir]\tCambia (o muestra) el directorio actual del shell\n"},
        {"fecha", cmdFecha, "uso: fecha [-d|-h]\tMuestra la fecha y o la hora actual\n"},
        {"hist", cmdHist, "uso: hist [-c|-N]\tMuestra el historico de comandos, con -c lo borra\n"},
        {"comando", cmdComando, "uso: comando [-N]\tRepite el comando N (del historico)\n"},
        {"infosis", cmdInfosis, "uso: infosis \tMuestra informacion de la maquina donde corre el shell\n"},
        {"ayuda", cmdAyuda, "uso: ayuda [cmd]\tMuestra ayuda sobre los comandos\n"},
        {"fin", cmdExit, "uso: fin \tTermina la ejecucion del shell\n"},
        {"salir", cmdExit, "uso: salir \tTermina la ejecucion del shell\n"},
        {"bye", cmdExit, "uso: bye \tTermina la ejecucion del shell\n"},
        {NULL, NULL, NULL}
};

void execute(int nTrozos, char* trozos[]){
    for (int i = 0; i < 9; i++) {
        if (strcmp(trozos[0], cmdTable[i].name) == 0) {
            cmdTable[i].function(nTrozos, &trozos[1]);
            break;
        }
    }
    cmdError();
}
*/
void processCmd(bool* finished, char* trozos[], tList *L, int* cmdNumber, int nTrozos) {
    if (nTrozos != 0) {
        if (strcmp(trozos[0], "autores") == 0) {
            cmdAutores(trozos[1]);
        }
        else if (strcmp(trozos[0], "pid") == 0) {
            cmdPid(trozos[1]);
        }
        else if (strcmp(trozos[0], "carpeta") == 0) {
            cmdCarpeta(trozos[1]);
        }
        else if (strcmp(trozos[0], "fecha") == 0) {
            cmdFecha(trozos[1]);
        }
        else if (strcmp(trozos[0], "hist") == 0) {
            cmdHist(L, trozos[1], cmdNumber);
        }
        else if (strcmp(trozos[0], "comando") == 0) {
            cmdComando(trozos[1], finished, trozos, L, cmdNumber, nTrozos);
        }
        else if (strcmp(trozos[0], "infosis") == 0) {
            cmdInfosis();
        }
        else if (strcmp(trozos[0], "ayuda") == 0) {
            cmdAyuda(trozos[1]);
        }
        else if (strcmp(trozos[0], "salir") == 0 || strcmp(trozos[0], "fin") == 0 || strcmp(trozos[0], "bye") == 0) {
            cmdExit(finished, trozos[1], L);
        }
        else{
            cmdError();
        }
    } else {
        cmdError();
    }
}

void cmdError(){
    printf("ERROR: comando invalido\n");
}

void cmdAutores(char* opcion) {
    if (opcion==NULL) {
        printf("Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es\n");
        printf("Lucia Alvarez Garcia: l.alvarezg@udc.es\n");
    }else if (strcmp(opcion, "-l") == 0) {
        printf("manuel.amestoy@udc.es\nl.alvarezg@udc.es\n");
    }else if (strcmp(opcion, "-n") == 0) {
        printf("Jose Manuel Amestoy Lopez\n");
        printf("Lucia Alvarez Garcia\n");
    } else {
        cmdError();
    }
}
void cmdPid(char* opcion){
    if (opcion == NULL) {
        printf("%d\n", getpid());
    } else if (strcmp(opcion, "-p") == 0) {
        printf("%d\n", getppid());
    } else {
        cmdError();
    }
}

void cmdCarpeta(char* opcion){
    const int MAX_STRING = 150;
    char string[MAX_STRING];

    if(opcion == NULL)
        printf("%s\n", getcwd(string, MAX_STRING));
    else if (chdir(opcion) == -1)
            printf("%s\n", strerror(errno));
}

void cmdFecha(char* opcion){
    if(opcion == NULL){
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("%02d:%02d:%02d\n%02d-%02d-%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }
    else if(strcmp(opcion, "-h") == 0){
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
    }
    else if(strcmp(opcion, "-d") == 0){
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("%02d-%02d-%02d\n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }
}

void cmdHist(tList *L, char* opcion, int* cmdNumber) {
    if (opcion == NULL) {
        tPosL p = first(*L);
        while (p != LNULL) {
            printf("%d->",p->data.number);
            printf("%s", p->data.command);
            p = p->next;
        }
    }
    else if (strcmp(opcion, "-c") == 0) {
        clearOutList(L);
        *cmdNumber = 0;
    }
    else if ((abs(atoi(opcion))) != -1){
        int n = abs(atoi(opcion));
        tPosL p = first(*L);

        for (int i = 0; i < n; ++i) {
            if (p == NULL) {
                printf("ERROR: El historial no tiene tantos elementos\n");
                break;
            }

            printf("%d->%s", p->data.number, p->data.command);
            p = p->next;
        }
    }
}

void cmdComando(char* opcion, bool* finished, char* trozos[], tList *L, int* cmdNumber, int nTrozos){
    if (opcion == NULL) {
        cmdHist(L, LNULL, cmdNumber);
    } else if (atoi(opcion) == 48) {
        tItemL d, h;
        tPosL p;
        d.number = 0;
        p = findItem(d, *L);
        d = getItem(p, *L);
        printf("Ejecutando hist %d: %s",d.number, h.command);
        TrocearCadena(h.command, trozos);
        processCmd(finished, trozos, L, cmdNumber, nTrozos);
    } else if(atoi(opcion) > last(*L)->data.number || atoi(opcion) < 0)
        printf("No hay elemento %s en el historico\n", opcion);
    else {
        tItemL d, h;
        tPosL p;
        d.number = abs(atoi(opcion));
        p = findItem(d, *L);
        h = getItem(p, *L);
        printf("Ejecutando hist %d: %s",d.number, h.command);
        TrocearCadena(h.command, trozos);
        processCmd(finished, trozos, L, cmdNumber, nTrozos);
    }
}

void cmdInfosis(){
        struct utsname data;
        uname(&data);
        printf("%s (%s), OS: %s-%s-%s\n", data.nodename, data.machine, data.sysname, data.release, data.version);
}

void cmdAyuda(char* opcion){
    if (opcion == NULL) {
        printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\n"
               "fin salir bye fecha pid autores hist comando carpeta infosis ayuda \n");
    }
    else if (strcmp(opcion, "fin") == 0) { printf("fin \tTermina la ejecucion del shell\n");}
    else if (strcmp(opcion, "salir") == 0) { printf("salir \tTermina la ejecucion del shell\n");}
    else if (strcmp(opcion, "bye") == 0) { printf("bye \tTermina la ejecucion del shell\n");}
    else if (strcmp(opcion, "fecha") == 0) { printf("fecha [-d|-h]\tMuestra la fecha y o la hora actual\n");}
    else if (strcmp(opcion, "pid") == 0) { printf("pid [-p]\tMuestra el pid del shell o de su proceso padre\n");}
    else if (strcmp(opcion, "autores") == 0) { printf("autores [-n|-l]\tMuestra los nombres y logins de los autores\n");}
    else if (strcmp(opcion, "hist") == 0) { printf("hist [-c|-N]\tMuestra el historico de comandos, con -c lo borra\n");}
    else if (strcmp(opcion, "comando") == 0) { printf("comando [-N]\tRepite el comando N (del historico)\n");}
    else if (strcmp(opcion, "carpeta") == 0) { printf("carpeta [dir]\tCambia (o muestra) el directorio actual del shell\n");}
    else if (strcmp(opcion, "infosis") == 0) { printf("infosis \tMuestra informacion de la maquina donde corre el shell\n");}
    else if (strcmp(opcion, "ayuda") == 0) { printf("ayuda [cmd]\tMuestra ayuda sobre los comandos\n");}
    else {
        printf("%s no encontrado\n", opcion);
    }
}
void cmdExit(bool* finished, const char* opcion, tList *L) {
    if(opcion == NULL) {
        clearOutList(L);
        *finished = true;
    } else {
        cmdError();
    }
}

int TrocearCadena(char* cadena, char* trozos[]) {
    int i = 1;

    if((trozos[0] = strtok(cadena, " \n\t")) == NULL)
        return 0;
    while((trozos[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
}