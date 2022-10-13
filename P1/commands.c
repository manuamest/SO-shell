/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */
#include "commands.h"
struct cmdEntry cmdTable[] = {
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
        {"create", cmdCreate, "uso: create [-f] [name]\tCrea un directorio o un fichero (-f)\n"},
        {"stat", cmdStat, "uso: stat [-long][-link][-acc] name1 name2 ..\tlista ficheros;\n"
                          "\t\t-long: listado largo\n\t\t-acc: acesstime\n"
                          "\t\t-link: si es enlace simbolico, el path contenido\n"},
        {"list", cmdList, "uso: list [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 ..\tlista contenidos de directorios\n"
                          "\t\t-hid: incluye los ficheros ocultos\n\t\t-reca: recursivo (antes)\n"
                          "\t\t-recb: recursivo (despues)\n\t\tresto parametros como stat\n"},
        {"delete", cmdDelete, "uso: delete [name1 name2 ..]\tBorra ficheros o directorios vacios\n"},
        {"deltree", cmdDeltree, "uso: deltree [name1 name2 ..]\tBorra ficheros o directorios no vacios recursivamente\n"},
        {NULL, NULL, NULL}
};

int execute(char* trozos[], int nTrozos, datos* data){
    if (trozos[0] == NULL) {
        return 0;
    } else {
        for (int i = 0; i < 16; i++) {
            if (strcmp(trozos[0], cmdTable[i].name) == 0) {
                return cmdTable[i].function(&trozos[1], nTrozos, data);
            }
        }
    }
}

void cmdError(){
    printf("ERROR: comando invalido\n");
}

int cmdAutores(char* opcion[], int nTrozos, datos* data) {
    if (opcion[0] == NULL) {
        printf("Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es\n");
        printf("Lucia Alvarez Garcia: l.alvarezg@udc.es\n");
    }else if (strcmp(opcion[0], "-l") == 0) {
        printf("manuel.amestoy@udc.es\nl.alvarezg@udc.es\n");
    }else if (strcmp(opcion[0], "-n") == 0) {
        printf("Jose Manuel Amestoy Lopez\n");
        printf("Lucia Alvarez Garcia\n");
    } else {
        cmdError();
    }
    return 1;
}

int cmdPid(char* opcion[], int nTrozos, datos* data){
    if (opcion[0] == NULL) {
        printf("%d\n", getpid());
    } else if (strcmp(opcion[0], "-p") == 0) {
        printf("%d\n", getppid());
    } else {
        cmdError();
    }
    return 1;
}

int cmdCarpeta(char* opcion[], int nTrozos, datos* data){
    const int MAX_STRING = 150;
    char string[MAX_STRING];

    if(opcion[0] == NULL)
        printf("%s\n", getcwd(string, MAX_STRING));
    else if (chdir(opcion[0]) == -1)
        printf("%s\n", strerror(errno));
    return 1;
}

int cmdFecha(char* opcion[], int nTrozos, datos* data){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    if(opcion[0] == NULL){
        printf("%02d:%02d:%02d\n%02d-%02d-%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }
    else if(strcmp(opcion[0], "-h") == 0){
        printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
    }
    else if(strcmp(opcion[0], "-d") == 0){
        printf("%02d-%02d-%02d\n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }
    return 1;
}

int cmdHist (char* opcion[], int nTrozos, datos* data) {
    if (opcion[0] == NULL) {
        tPosL p = first(data->list);
        while (p != LNULL) {
            printf("%d->",p->data.number);
            printf("%s", p->data.command);
            p = p->next;
        }
    }
    else if (strcmp(opcion[0], "-c") == 0) {
        clearOutList(&data->list);
        data->cmdNumber = 0;
    }
    else if ((abs(atoi(opcion[0]))) != -1){
        int n = abs(atoi(opcion[0]));
        tPosL p = first(data->list);

        for (int i = 0; i < n; ++i) {
            if (p == NULL) {
                printf("ERROR: El historial no tiene tantos elementos\n");
                break;
            }

            printf("%d->%s", p->data.number, p->data.command);
            p = p->next;
        }
    }
    return 1;
}

int cmdComando(char* opcion[], int nTrozos, datos* data){
    if (opcion[0] == NULL) {
        cmdHist(opcion, nTrozos, data);
    } else if (atoi(opcion[0]) == 48) {
        tItemL d, h;
        tPosL p;
        d.number = 0;
        p = findItem(d, data->list);
        d = getItem(p, data->list);
        printf("Ejecutando hist %d: %s",d.number, h.command);
        TrocearCadena(h.command, opcion);
        execute(opcion, nTrozos, data);
    } else if(atoi(opcion[0]) > last(data->list)->data.number || atoi(opcion[0]) < 0)
        printf("No hay elemento %s en el historico\n", opcion[0]);
    else {
        tItemL d, h;
        tPosL p;
        d.number = abs(atoi(opcion[0]));
        p = findItem(d, data->list);
        h = getItem(p, data->list);
        printf("Ejecutando hist %d: %s",d.number, h.command);
        TrocearCadena(h.command, opcion);
        execute(opcion, nTrozos, data);
    }
    return 1;
}

int cmdInfosis(char* opcion[], int nTrozos, datos* data){
    struct utsname datasis;
    uname(&datasis);
    printf("%s (%s), OS: %s-%s-%s\n", datasis.nodename, datasis.machine, datasis.sysname, datasis.release, datasis.version);
    return 1;
}

int cmdAyuda(char* opcion[], int nTrozos, datos* data){
    if (opcion[0] == NULL) {
        printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\n"
               "fin salir bye fecha pid autores hist comando carpeta infosis ayuda \n");
    } else {
        for (int i = 0; i < 16; i++) {
            if (strcmp(opcion[0], cmdTable[i].name) == 0) {
                printf("%s", cmdTable[i].ayuda);
                break;
            }
        }
    }
    return 1;
}

int cmdCreate(char* opcion[], int nTrozos, datos* data){
    const int MAX_STRING = 150;
    char string[MAX_STRING];
    if (opcion[0] == NULL) {
        printf("%s\n", getcwd(string, MAX_STRING));
    } else {
        if (nTrozos > 1) {
            if (strcmp(opcion[0], "-f") == 0) {
                if (opcion[1] == NULL) {
                    printf("%s\n", getcwd(string, MAX_STRING));
                }else {
                    if(open(opcion[1],O_CREAT | O_EXCL , 0666) == -1) {
                        printf("Imposible crear: %s\n", strerror(errno));
                    }
                }
            } else {
                if (mkdir(opcion[0], 0755) == -1) {
                    printf("Imposible crear: %s\n", strerror(errno));
                }
            }
        }
    }
    return 1;
}

void printfInfo(char* path, bool lng, bool acc, bool link) {
    struct stat data;

    if(lstat(path, &data) == -1)
        printf("****error al acceder a %s: %s\n", path, strerror(errno));

    else {
        if (!lng) {
            printf("%ld  %s\n", data.st_size, path);
        } else {
            if (!acc) {
                time_t t = data.st_mtim.tv_sec;
                struct tm *tm = localtime(&t);
                struct passwd *pw = getpwuid(data.st_uid);
                struct group *gr = getgrgid(data.st_gid);
                printf("%d/%d/%d-%d:%d\t", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
                printf("%lu ( %lu)\t%s\t%s ", data.st_nlink, data.st_ino, pw->pw_name, gr->gr_name);
            } else {
                time_t t = data.st_atim.tv_sec;
                struct tm *tm = localtime(&t);
                struct passwd *pw = getpwuid(data.st_uid);
                struct group *gr = getgrgid(data.st_gid);
                printf("%d/%d/%d-%d:%d\t", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
                printf("%lu ( %lu)\t%s\t%s ", data.st_nlink, data.st_ino, pw->pw_name, gr->gr_name);
            }

            printf((S_ISDIR(data.st_mode)) ? "d" : "-");
            printf((data.st_mode & S_IRUSR) ? "r" : "-");
            printf((data.st_mode & S_IWUSR) ? "w" : "-");
            printf((data.st_mode & S_IXUSR) ? "x" : "-");
            printf((data.st_mode & S_IRGRP) ? "r" : "-");
            printf((data.st_mode & S_IWGRP) ? "w" : "-");
            printf((data.st_mode & S_IXGRP) ? "x" : "-");
            printf((data.st_mode & S_IROTH) ? "r" : "-");
            printf((data.st_mode & S_IWOTH) ? "w" : "-");
            printf((data.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t");
            printf("%ld  %s", data.st_size, path);

            if(link){
                char linkpath[150];
                long endlink = readlink(path, linkpath, 150);
                if(endlink != -1){
                    linkpath[endlink] = '\0';
                    printf(" -> %s\n", linkpath);
                } else printf("\n");
            } else
                printf("\n");
        }
    }
}

int cmdStat(char* opcion[], int nTrozos, datos* data){
    char string[150];

    if (opcion == NULL) {
        printf("%s\n", getcwd(string, 150));
    }
    else if (opcion[0] != NULL){
        bool lng = false, acc = false, link = false;
        int i;

        for (i = 0; opcion[i+1] != NULL; i++){
            if (strcmp(opcion[i], "-long") == 0)
                lng = true;
            if(strcmp(opcion[i], "-acc") == 0)
                acc = true;
            if(strcmp(opcion[i], "-link") == 0)
                link = true;
        }

        if (strcmp(opcion[i], "-long") == 0 || strcmp(opcion[i], "-link") == 0 || strcmp(opcion[i], "-acc") == 0){
            printf("%s\n", getcwd(string, 150));
        } else
            printfInfo(opcion[i], lng, acc, link);
    } else {
        cmdError();
    }
    return 1;
}

int cmdList(char* opcion[], int nTrozos, datos* data){
    return 1;
}

int cmdDelete(char* opcion[], int nTrozos, datos* data1){
    const int MAX_STRING = 150;
    char string[MAX_STRING];
    if (opcion[0] == NULL) {
        printf("%s\n", getcwd(string, MAX_STRING));
    } else {
        if (rmdir(opcion[0]) == -1) {
            printf("Imposible borrar carpeta: %s\n", strerror(errno));
        }
        if (unlink(opcion[0]) == -1) {
            printf("Imposible borrar fichero: %s\n", strerror(errno));
        }
    }
}

int cmdDeltree(char* opcion[], int nTrozos, datos* data){
    return 1;
}

int cmdExit(char* opcion[], int nTrozos, datos* data) {
    if(opcion[0] == NULL) {
        clearOutList(&data->list);
        data->finished = true;
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