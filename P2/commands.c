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
        {"allocate", cmdAllocate, "uso: allocate [-malloc|-shared|-createshared|-mmap]... Asigna un bloque de memoria\n"
                                  "\t-malloc tam: asigna un bloque malloc de tamano tam\n"
                                  "\t-createshared cl tam: asigna (creando) el bloque de memoria compartida de clave cl y tamano tam\n"
                                  "\t-shared cl: asigna el bloque de memoria compartida (ya existente) de clave cl\n"
                                  "\t-mmap fich perm: mapea el fichero fich, perm son los permisos"},
        {"deallocate", cmdDeallocate, "uso: deallocate [-malloc|-shared|-delkey|-mmap|addr]..\tDesasigna un bloque de memoria\n"
                                      "\t-malloc tam: desasigna el bloque malloc de tamano tam\n"
                                      "\t-shared cl: desasigna (desmapea) el bloque de memoria compartida de clave cl\n"
                                      "\t-delkey cl: elimina del sistema (sin desmapear) la clave de memoria cl\n"
                                      "\t-mmap fich: desmapea el fichero mapeado fich\n"
                                      "\taddr: desasigna el bloque de memoria en la direccion addr"},
        {"i-o", cmdio, "uso: i-o [read|write] [-o] fiche addr cont \n"
                       "\tread fich addr cont: Lee cont bytes desde fich a addr\n"
                       "\twrite [-o] fich addr cont: Escribe cont bytes desde addr a fich. -o para sobreescribir\n"
                       "\t\taddr es una direccion de memoria"},
        {"memdump", cmdMemdump, "uso: memdump addr cont \tVuelca en pantallas los contenidos (cont bytes) de la posicion de memoria addr"},
        {"memfill", cmdMemfill, "uso: memfill addr cont byte \tLlena la memoria a partir de addr con byte"},
        {"memory", cmdMemory, "uso: memory [-blocks|-funcs|-vars|-all|-pmap] ..\tMuestra muestra detalles de la memoria del proceso\n"
                              "\t\t-blocks: los bloques de memoria asignados\n"
                              "\t\t-funcs: las direcciones de las funciones\n"
                              "\t\t-vars: las direcciones de las variables\n"
                              "\t\t:-all: todo\n"
                              "\t\t-pmap: muestra la salida del comando pmap(o similar)"},
        {"recurse", cmdRecurse, "uso: recurse [n]\tInvoca a la funcion recursiva n veces"},
        {NULL, NULL, NULL}
};

int execute(char* trozos[], int nTrozos, datos* data){
    if (trozos[0] == NULL) {
        return 0;
    } else {
        for (int i = 0; i < NCOMMANDS; i++) {
            if (strcmp(trozos[0], cmdTable[i].name) == 0) {
                return cmdTable[i].function(&trozos[1], nTrozos, data);
            }
        }
        printf("No ejecutado: No such file or directory\n");
    }

    return 1;
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
        for (int i = 0; i < NCOMMANDS; i++) {
            if (strcmp(opcion[0], cmdTable[i].name) == 0) {
                printf("%s", cmdTable[i].ayuda);
                break;
            }
        }
        printf("%s no encontrado\n", opcion[0]);
    }
    return 1;
}

int cmdExit(char* opcion[], int nTrozos, datos* data) {
    if(opcion[0] == NULL) {
        data->finished = true;
    } else {
        cmdError();
    }
    return 1;
}

int TrocearCadena(char* cadena, char* trozos[]) {
    int i = 1;

    if((trozos[0] = strtok(cadena, " \n\t")) == NULL)
        return 0;
    while((trozos[i] = strtok(NULL, " \n\t")) != NULL)
        i++;
    return i;
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

char LetraTF (mode_t m) {
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char* ConvierteModo (mode_t m) {
    static char permisos[12];
    strcpy (permisos,"---------- ");

    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}

void printfInfo(char* path, bool lng, bool acc, bool link, bool hid) {
    struct stat data;

    char file_name[100];
    int last_dir = 1, j = 0;

    for(int i = 0; path[i] != '\0'; i++){
        if(path[i] == '/')
            last_dir = i;
    }

    for(int i = last_dir + 1; path[i] != '\0'; i++){
        file_name[j] = path[i];
        j++;
    }

    file_name[j] = '\0';

    if(lstat(path, &data) == -1)
        printf("****error al acceder a %s: %s\n", path, strerror(errno));

    else {

        if (!hid && (file_name[0] == '.' || file_name[strlen(file_name)-1] == '~') && strcmp(path, "..") != 0 && strcmp(path, ".") != 0 )
            ;           // si es un archivo oculto / backup entonces sólo se muestra si hid = true.
        else {
            if (!lng) {
                printf("%8ld  %s\n", data.st_size, file_name);
            } else {
                if (!acc) {
                    time_t t = data.st_mtim.tv_sec;
                    struct tm *tm = localtime(&t);
                    struct passwd *pw = getpwuid(data.st_uid);
                    struct group *gr = getgrgid(data.st_gid);
                    printf("%04d/%02d/%02d-%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
                    printf("%4lu (%8lu) %8s %8s ", data.st_nlink, data.st_ino, pw->pw_name, gr->gr_name);
                } else {
                    time_t t = data.st_atim.tv_sec;
                    struct tm *tm = localtime(&t);
                    struct passwd *pw = getpwuid(data.st_uid);
                    struct group *gr = getgrgid(data.st_gid);
                    printf("%04d/%02d/%02d-%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
                    printf("%4lu (%8lu) %8s %8s ", data.st_nlink, data.st_ino, pw->pw_name, gr->gr_name);
                }

                char* permisos = ConvierteModo(data.st_mode);
                printf("%s\t", permisos);
                printf("%8ld  %s", data.st_size, file_name);

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
}

int cmdStat(char* opcion[], int nTrozos, datos* data){
    char string[150];

    if (opcion[0] == NULL) {
        printf("%s\n", getcwd(string, 150));
    }
    else{
        bool lng = false, acc = false, link = false;
        bool changes = true;
        int i;

        for (i = 0; (opcion[i+1] != NULL) && (changes == true); i++){
            changes = false;
            if (strcmp(opcion[i], "-long") == 0){
                lng = true;
                changes = true;
            }
            if(strcmp(opcion[i], "-acc") == 0){
                acc = true;
                changes = true;
            }
            if(strcmp(opcion[i], "-link") == 0){
                link = true;
                changes = true;
            }
        }

        if (strcmp(opcion[i], "-long") == 0 || strcmp(opcion[i], "-link") == 0 || strcmp(opcion[i], "-acc") == 0){ // en caso de que se pongan las flags y no el elemento
            printf("%s\n", getcwd(string, 150));
        } else {
            if ((nTrozos == 2 && i == 0) || strcmp(opcion[i-1], "-long") == 0 || strcmp(opcion[i-1], "-link") == 0 || strcmp(opcion[i-1], "-acc") == 0)  // stat de 1 elemento sin flags
                printfInfo(opcion[i], lng, acc, link, true);
            else{
                for(i = i-1; opcion[i] != NULL; ++i){   // stat de varios elementos
                    printfInfo(opcion[i], lng, acc, link, true);
                }
            }
        }

    }

    return 1;
}

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

void recursive(char* path, bool lng, bool acc, bool link, bool hid, bool reca, bool recb) {
    DIR *d;
    struct dirent *itemInfo;

    struct stat data;
    lstat(path, &data);     // para el S_ISDIR()


    if (!S_ISDIR(data.st_mode))       // si originalmente se metió un archivo en recursive() en lugar de un directorio
        printfInfo(path, lng, acc, link, hid);
    else if ((d = opendir(path)) == NULL)           // si hubo fallo al abrir el directorio
        printf("%s\n", strerror(errno));

    else if (reca) {
        char new_path[150];
        int len;

        strcpy(new_path, strcat(path, "/"));
        path[strlen(path) - 1] = '\0';      // eliminar el "/" que se acaba de colocar en path
        len = strlen(new_path) + 1;

        printf("************%s\n", path);
        while ((itemInfo = readdir(d)) != NULL) {
            strcat(new_path, itemInfo->d_name);
            printfInfo(new_path, lng, acc, link, hid);
            new_path [len - 1] = '\0';
        }
        closedir(d);
        if((d = opendir(path)) == NULL)
            printf("%s\n", strerror(errno));

        while ((itemInfo = readdir(d)) != NULL) {
            if ((itemInfo->d_name[0] == '.' || itemInfo->d_name[strlen(itemInfo->d_name)-1] == '~') && !hid);
            else {
                if(itemInfo->d_type == DT_DIR && strcmp(itemInfo->d_name, "..") != 0 && strcmp(itemInfo->d_name, ".") != 0) {  // entramos a los directorios de la carpeta introducida y mostramos sus elementos
                    strcat(new_path, itemInfo->d_name);
                    recursive(new_path, lng, acc, link, hid, reca, recb);
                    new_path [len - 1] = '\0';
                }
            }
        }
    }else if (recb) {

        char new_path[150];
        int len;

        strcpy(new_path, strcat(path, "/"));
        path[strlen(path) - 1] = '\0';      // eliminar el "/" que se acaba de colocar en path
        len = strlen(new_path) + 1;
        while ((itemInfo = readdir(d)) != NULL) {
            if ((itemInfo->d_name[0] == '.' || itemInfo->d_name[strlen(itemInfo->d_name) - 1] == '~') && !hid);
            else {
                if (itemInfo->d_type == DT_DIR && strcmp(itemInfo->d_name, "..") != 0 &&
                        strcmp(itemInfo->d_name, ".") != 0) {  // entramos a los directorios de la carpeta introducida y mostramos sus elementos
                        strcat(new_path, itemInfo->d_name);
                        recursive(new_path, lng, acc, link, hid, reca, recb);
                        new_path[len - 1] = '\0';
                }
            }
        }
        printf("************%s\n", path);
        closedir(d);
        if ((d = opendir(path)) == NULL)
            printf("%s\n", strerror(errno));

        while ((itemInfo = readdir(d)) != NULL) {
            strcat(new_path, itemInfo->d_name);
            printfInfo(new_path, lng, acc, link, hid);
            new_path[len - 1] = '\0';
        }
    } else {      // si no se usa ni -reca ni -recb sólo mostramos lo del directorio dado
            char new_path[150];
            int len;

            strcpy(new_path, strcat(path, "/"));
            path[strlen(path) - 1] = '\0';      // eliminar el "/" que se acaba de colocar en path
            len = strlen(new_path) + 1;

            printf("************%s\n", path);

            while ((itemInfo = readdir(d)) != NULL) {
                strcat(new_path, itemInfo->d_name);
                printfInfo(new_path, lng, acc, link, hid);
                new_path[len - 1] = '\0';
            }
    }
    closedir(d);
}

int cmdList(char* opcion[], int nTrozos, datos* data){
    char string[150];

    if (opcion[0] == NULL) {
        printf("%s\n", getcwd(string, 150));
    }

    else {
        bool lng = false, acc = false, link = false, hid = false, reca = false, recb = false;
        bool changes = true;
        int i;

        for (i = 0; (opcion[i+1] != NULL) && (changes == true); i++){
            changes = false;
            if (strcmp(opcion[i], "-long") == 0){
                lng = true;
                changes = true;
            }
            if(strcmp(opcion[i], "-acc") == 0){
                acc = true;
                changes = true;
            }
            if(strcmp(opcion[i], "-link") == 0){
                link = true;
                changes = true;
            }
            if(strcmp(opcion[i], "-hid") == 0){
                hid = true;
                changes = true;
            }
            if(strcmp(opcion[i], "-reca") == 0){
                reca = true;
                changes = true;
            }
            if(strcmp(opcion[i], "-recb") == 0){
                recb = true;
                changes = true;
            }
        }

        if (strcmp(opcion[i], "-long") == 0 || strcmp(opcion[i], "-link") == 0 || strcmp(opcion[i], "-acc") == 0
            || strcmp(opcion[i], "-hid") == 0 || strcmp(opcion[i], "-reca") == 0 || strcmp(opcion[i], "-recb") == 0){  // en caso de que se pongan las flags y no el elemento
            printf("%s\n", getcwd(string, 150));
        } else {
            if ((nTrozos == 2 && i == 0) || strcmp(opcion[i-1], "-long") == 0 || strcmp(opcion[i-1], "-link") == 0 || strcmp(opcion[i-1], "-acc") == 0
                || strcmp(opcion[i-1], "-hid") == 0 || strcmp(opcion[i-1], "-reca") == 0 || strcmp(opcion[i-1], "-recb") == 0) {  // en caso de que sólo se quiera hacer list de 1 elemento

                recursive(opcion[i], lng, acc, link, hid, reca, recb);

            }
            else{
                for(i = i-1; opcion[i] != NULL; ++i){                           // list de varios elementos
                    strcpy(string, opcion[i]);
                    recursive(string, lng, acc, link, hid, reca, recb);
                    string[0] = '\0';
                }
            }
        }

    }

    return 1;
}

int cmdDelete(char* opcion[], int nTrozos, datos* data1){
    const int MAX_STRING = 150;
    char string[MAX_STRING];
    if (opcion[0] == NULL) {
        printf("%s\n", getcwd(string, MAX_STRING));
    } else {
        for (int i = 0; i < nTrozos-1 ; i++) {
            if (remove(opcion[i]) == -1) {
                printf("Imposible borrar %s: %s\n", opcion[i], strerror(errno));
            }
        }
    }
    return 1;
}


int removeRecursivo(char* directory) {
    DIR *d;
    struct dirent *itemInfo;
    char path[1024];

    if((d = opendir(directory)) == NULL) return -1;

    while ((itemInfo=readdir(d)) != NULL) {
        strcpy(path, directory);
        strcat(path, "/");
        strcat(path, itemInfo->d_name);
        if(strcmp(itemInfo->d_name, ".") == 0 || strcmp(itemInfo->d_name, "..") == 0) continue;

        if(isDirectory(path)){
            removeRecursivo(path);
        }
        if(remove(path))return -1;
    }
    closedir(d);
    return 0;
}

int cmdDeltree(char* opcion[], int nTrozos, datos* data){
    const int MAX_STRING = 150;
    char string[MAX_STRING];

    if (opcion[0] == NULL) {
        printf("%s\n", getcwd(string, MAX_STRING));
    } else {
        for (int i = 0; i < nTrozos-1; i++) {
            if (isDirectory(opcion[i])) {
                if (rmdir(opcion[i]) == -1) {
                    if (removeRecursivo(opcion[i]) == -1 || rmdir(opcion[i])) {
                        printf("Imposible borrar %s: %s\n", opcion[i], strerror(errno));
                    }
                }
            } else {
                if (unlink(opcion[i]) == -1) {
                    printf("Imposible borrar %s: %s\n", opcion[i], strerror(errno));
                }
            }
        }
    }
    return 1;
}

void list_Allocations(int type, tList memList) {
    char* listType;
    switch (type) {
        case 1: listType = "malloc"; break;
        case 2: listType = "shared"; break;
        case 3: listType = "mmap"; break;
        default: listType = ""; break;
    }

    if (type >= 0 && type <= 3) {
        if(type == 0)
            printf("******Lista de bloques asignados para el proceso %d\n", getpid());
        else
            printf("******Lista de bloques asignados %s para el proceso %d\n", listType, getpid());

        if(!isEmptyList(memList)){
            for(tPosL i = first(memList); i != NULL; i = i->next) {
                if(type == 0 || i->data.allocType == type) {
                    char* month;
                    switch (i->data.allocTime.tm_mon) {
                        case 0: month = "Jan"; break;
                        case 1: month = "Feb"; break;
                        case 2: month = "Mar"; break;
                        case 3: month = "Apr"; break;
                        case 4: month = "May"; break;
                        case 5: month = "Jun"; break;
                        case 6: month = "Jul"; break;
                        case 7: month = "Aug"; break;
                        case 8: month = "Sep"; break;
                        case 9: month = "Oct"; break;
                        case 10: month = "Nov"; break;
                        case 11: month = "Dec"; break;
                    }
                    if(i->data.allocType == 1) listType = "malloc";
                    else if(i->data.allocType == 2) listType = "shared";
                    else if(i->data.allocType == 3) listType = "mmap";

                    printf("      %-23p %6zu %3s %2d %02d:%02d", i->data.blockAddress, i->data.blockSize, month,
                           i->data.allocTime.tm_mday, i->data.allocTime.tm_hour, i->data.allocTime.tm_min);

                    if(i->data.allocType == 1) printf(" malloc");
                    else if(i->data.allocType == 2) printf(" shared (key %d)", i->data.keySh);
                    else if(i->data.allocType == 3) printf(" %s  (descriptor %d)", i->data.fileName, i->data.fileDescriptor);
                    printf("\n");
                }
            }
        }
    }
    else
        printf("uso: allocate [-malloc|-shared|-createshared|-mmap] ....\n");
}

void allocate_malloc(datos* data, size_t tam) {
    void* dir = malloc(tam);
    if(dir == NULL)
        printf("No queda suficiente espacio para reservar tanta memoria.\n");
    else {
        time_t t = time(NULL);              // creamos el nuevo item y lo metemos en la lista
        tItemL item;
        item.blockAddress = dir;
        item.blockSize = tam;
        item.allocTime = *localtime(&t);
        item.allocType = 1;     // == malloc
        insertItem(item, &data->memoryList);
        printf("Asignados %zu bytes en %p\n", tam, dir);
    }
}

void insertarNodoShared (tList* L, void* dir, size_t tam, key_t cl) {
    time_t t = time(NULL);
    tItemL item;
    item.blockAddress = dir;
    item.blockSize = tam;
    item.keySh = cl;
    item.allocTime = *localtime(&t);
    item.allocType = 2;     // == shared
    insertItem(item, L);
}

void* ObtenerMemoriaShmget (key_t clave, size_t tam, datos* data) {
    void* p;
    int aux, id, flags = 0777;
    struct shmid_ds s;

    if(tam != 0)     /* tam distito de 0 indica crear */
        flags = flags | IPC_CREAT | IPC_EXCL;

    if(clave == IPC_PRIVATE){  /*no nos vale*/
        errno = EINVAL;
        return NULL;
    }

    if((id = shmget(clave, tam, flags)) == -1)
        return NULL;

    if((p = shmat(id,NULL,0)) == (void*) -1){
        aux = errno;
        if(tam != 0)
            shmctl(id,IPC_RMID,NULL);
        errno = aux;
        return NULL;
    }
    shmctl(id,IPC_STAT,&s);
    insertarNodoShared (&data->memoryList, p, s.shm_segsz, clave);

    return (p);
}

void allocate_createshared(char* opcion[], datos* data) {
    key_t cl;
    size_t tam;
    void* p;

    cl = (key_t) strtoul(opcion[1],NULL,10);
    tam = (size_t) strtoul(opcion[2],NULL,10);
    if (tam == 0) {
        printf("No se asignan bloques de 0 bytes\n");
        return;
    }
    if ((p = ObtenerMemoriaShmget(cl,tam, data))!=NULL)
        printf ("Asignados %zu bytes en %p\n", tam, p);
    else
        printf ("Imposible asignar memoria compartida clave %d: %s\n", cl,strerror(errno));
}

void insertarNodoMmap (tList* L, void* dir, size_t tam, int df, char* fichero) {
    time_t t = time(NULL);
    tItemL item;
    item.blockAddress = dir;
    item.blockSize = tam;
    item.fileDescriptor = df;
    strcpy(item.fileName, fichero);
    item.allocTime = *localtime(&t);
    item.allocType = 3;     // == mmap
    insertItem(item, L);
}

void* MapearFichero (char* fichero, int protection, datos* data) {
    int df, map = MAP_PRIVATE, modo = O_RDONLY;
    struct stat s;
    void *p;

    if (protection&PROT_WRITE)
        modo = O_RDWR;
    if (stat(fichero,&s) == -1 || (df = open(fichero, modo)) == -1)
        return NULL;
    if ((p = mmap(NULL,s.st_size, protection,map,df,0)) == MAP_FAILED)
        return NULL;
    insertarNodoMmap (&data->memoryList,p, s.st_size,df,fichero);

    return p;
}

void do_AllocateMmap(char *arg[], datos* data) {
    char *perm;
    void *p;
    int protection = 0;

    if ((perm = arg[1]) != NULL && strlen(perm) < 4) {
        if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
        if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
        if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
    }
    if ((p = MapearFichero(arg[0], protection, data)) == NULL)
        perror ("Imposible mapear fichero");
    else
        printf ("fichero %s mapeado en %p\n", arg[0], p);
}

int cmdAllocate(char* opcion[], int nTrozos, datos* data) {
    if(nTrozos == 1)
        list_Allocations(0, data->memoryList);
    else{
        if(strcmp(opcion[0], "-malloc") == 0) {
            if(nTrozos != 3)
                list_Allocations(1, data->memoryList);
            else {
                // funcion malloc
                size_t tam = strtol(opcion[1], NULL, 10);
                if(tam == 0)
                    printf("No se asignan bloques de 0 bytes\n");
                else
                    allocate_malloc(data, tam);
            }
        }
        else if(strcmp(opcion[0], "-createshared") == 0) {
            if(nTrozos != 4)
                list_Allocations(2, data->memoryList);
            else {
                // función createshared
                allocate_createshared(opcion, data);
            }
        }
        else if(strcmp(opcion[0], "-shared") == 0) {
            if(nTrozos != 3)
                list_Allocations(2, data->memoryList);
            else {
                // función shared
                void* p;
                key_t cl = (key_t) strtoul(opcion[1],NULL,10);
                if ((p = ObtenerMemoriaShmget(cl, 0, data)) != NULL)
                    printf ("Memoria compartida de clave %d en %p\n", cl, p);
                else
                    printf ("Imposible asignar memoria compartida clave %d: %s\n", cl, strerror(errno));
            }
        }
        else if(strcmp(opcion[0], "-mmap") == 0) {
            if(nTrozos != 4 && nTrozos != 3)
                list_Allocations(3, data->memoryList);
            else {
                // función mmap
                do_AllocateMmap(&opcion[1], data);
            }
        }
        else
            printf("uso: allocate [-malloc|-shared|-createshared|-mmap] ....\n");
    }

    return 1;
}

void do_DeallocateDelkey (char *args[]) {
    key_t clave;
    int id;
    char* key = args[0];

    if (key == NULL || (clave = (key_t) strtoul(key, NULL, 10)) == IPC_PRIVATE){
        printf("      delkey necesita clave_valida\n");
        return;
    }
    if ((id = shmget(clave, 0, 0666)) == -1){
        perror("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id, IPC_RMID, NULL) == -1)
        perror("shmctl: imposible eliminar memoria compartida\n");
}

int cmdDeallocate(char* opcion[], int nTrozos, datos* data) {
    if(nTrozos == 1)
        list_Allocations(0, data->memoryList);
    else {
        if (strcmp(opcion[0], "-malloc") == 0) {
            //funcion malloc
            if (nTrozos != 3)
                list_Allocations(1, data->memoryList);
            else {
                long tam = strtol(opcion[1], NULL, 10);
                if(tam == 0)
                    printf("No se asignan bloques de 0 bytes\n");
                else {
                    if(!isEmptyList(data->memoryList)) {
                        tPosL i;
                        for(i = first(data->memoryList); i->next != NULL && getItem(i, data->memoryList).blockSize != tam; i = i->next);
                        if(getItem(i, data->memoryList).blockSize == tam) {
                            tItemL item = getItem(i, data->memoryList);
                            free(item.blockAddress);
                            deleteAtPosition(i, &data->memoryList);
                        }
                        else
                            printf("No hay bloque de ese tamano asignado con malloc\n");
                    }
                    else
                        printf("No hay bloque de ese tamano asignado con malloc\n");
                }
            }
        }
        else if (strcmp(opcion[0], "-shared") == 0) {
            // función shared
            if (nTrozos != 3)
                list_Allocations(2, data->memoryList);
            else {
                key_t cl = (key_t) strtoul(opcion[1], NULL, 10);
                if(!isEmptyList(data->memoryList)) {
                    tPosL i;
                    for(i = first(data->memoryList); i->next != NULL && getItem(i, data->memoryList).keySh != cl; i = i->next);
                    if(getItem(i, data->memoryList).keySh == cl) {
                        tItemL item = getItem(i, data->memoryList);
                        if(shmdt(item.blockAddress) == -1)
                            printf("Error al desmapear la memoria: %s\n", strerror(errno));
                        else
                            deleteAtPosition(i, &data->memoryList);
                    }
                    else
                        printf("No hay bloque de esa clave mapeado en el proceso\n");
                }
                else
                    printf("No hay bloque de esa clave mapeado en el proceso\n");
            }
        }
        else if (strcmp(opcion[0], "-delkey") == 0) {
            if (nTrozos != 3)
                list_Allocations(2, data->memoryList);
            else {
                // función delkey
                do_DeallocateDelkey(&opcion[1]);
            }
        }
        else if (strcmp(opcion[0], "-mmap") == 0) {
            if (nTrozos != 3)
                list_Allocations(3, data->memoryList);
            else {
                // función mmap
                if(!isEmptyList(data->memoryList)) {
                    tPosL i;
                    for(i = first(data->memoryList); i->next != NULL && strcmp(getItem(i, data->memoryList).fileName, opcion[1]) != 0; i = i->next);
                    if(strcmp(getItem(i, data->memoryList).fileName, opcion[1]) == 0) {
                        tItemL item = getItem(i, data->memoryList);
                        if(munmap(item.blockAddress, item.blockSize) == -1)
                            printf("%s", strerror(errno));
                        else
                            deleteAtPosition(i, &data->memoryList);
                    }
                    else
                        printf("Fichero %s no mapeado\n", opcion[1]);
                }
                else
                    printf("Fichero %s no mapeado\n", opcion[1]);
            }
        }
        else {
            //función addr
            tPosL i;
            unsigned long dir = strtoul(opcion[0], NULL, 16);
            for(i = first(data->memoryList); i != NULL && (long) getItem(i, data->memoryList).blockAddress != dir; i = i->next);
            if(i != NULL) {
                tItemL item = getItem(i, data->memoryList);
                if(item.allocType == 1) {
                    free(i->data.blockAddress);
                    deleteAtPosition(i, &data->memoryList);
                }
                else if(item.allocType == 2) {
                    if(shmdt(item.blockAddress) == -1)
                        printf("Error al desmapear la memoria: %s\n", strerror(errno));
                    else
                        deleteAtPosition(i, &data->memoryList);
                }
                else {
                    if(munmap(item.blockAddress, item.blockSize) == -1)
                        printf("%s", strerror(errno));
                    else
                        deleteAtPosition(i, &data->memoryList);
                }
            }
            else printf("Direccion %p no asignada con malloc, shared o mmap", opcion[1]);
        }
    }
    return 1;
}

//----------------------------------------------||I-O||--------------------------------------
ssize_t LeerFichero (char *f, void *p, size_t cont)
{
    struct stat s;
    ssize_t  n;
    int df,aux;

    if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
        return -1;
    if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont=s.st_size;
    if ((n=read(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}

void* cadtop(char* addr) {
    void* p = (void *) strtoul(addr, NULL, 16);
    return p;
}

void do_I_O_read (char *ar[])
{
    void *p;
    size_t cont=-1;
    ssize_t n;
    if (ar[1]==NULL || ar[2]==NULL){
        printf ("faltan parametros\n");
        return;
    }

    p=cadtop(ar[2]);  /*convertimos de cadena a puntero*/
    if (ar[3]!=NULL)
        cont=(size_t) atoll(ar[3]);

    if ((n=LeerFichero(ar[1],p,cont))==-1)
        perror ("Imposible leer fichero");
    else
        printf ("leidos %lld bytes de %s en %p\n",(long long) n,ar[1],p);
}

ssize_t EscribirFichero (char *fich, void *p, ssize_t n){
    ssize_t nescritos,tam=n;
    int df, aux;
    df=open(fich,O_RDWR);
    if((nescritos=write(df,p,tam))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return (nescritos);
}
int cmdio(char* opcion[], int nTrozos, datos* data) {
    if (opcion[0] != NULL) {
        if (opcion[1] == NULL) {
            printf("faltan parametros\n");
            return -1;
        }
        if (strcmp(opcion[0], "read") == 0) {
            if (nTrozos >= 4) {
                do_I_O_read(opcion);
            } else {
                printf("faltan parametros\n");
                return -1;
            }
        } else if (strcmp(opcion[0], "write") == 0) {
            if (nTrozos <= 4) {
                printf("faltan parametros\n");
                return -1;
            }
            void *p;
            ssize_t cont = -1;
            ssize_t n;
            p = cadtop(opcion[2]);  /*convertimos de cadena a puntero*/
            if (opcion[3] != NULL)
                cont = atol(opcion[3]);
            if ((strcmp(opcion[1], "-o") == 0)) {
                if (opcion[2] == NULL || opcion[3] == NULL) {
                    printf("faltan parametros\n");
                    return 0;
                }
                creat(opcion[2], 0666);
                void* addr = (void *) strtoul(opcion[3], NULL, 16);
                if((n = EscribirFichero(opcion[2], addr, atol(opcion[4])))==-1)
                    perror("error de escritura");
                else
                    printf("escritos %zd bytes\n", n);
            } else if (open(opcion[1], O_CREAT | O_EXCL, 0666) != -1) {
                if ((n = EscribirFichero(opcion[1], p, cont)) == -1)
                    perror("error de escritura");
                else
                    printf("escritos %lld bytes\n", (long long) n);
            } else {
                printf("Imposible escribir fichero: %s\n", strerror(errno));
            }
        }
    }else printf("uso: i-o [read|write] ......\n");
    return 0;
}

int cmdMemdump(char* opcion[], int nTrozos, datos* data){
    if(opcion[0] != NULL){
        int cont = 25;
        if (opcion[1]!=NULL) cont = atoi(opcion[1]);
        long addr = strtoul(opcion[0],NULL,16);

        for(int i=0; i < cont; i+=25){
            long aux = addr;
            for(int j = 0; (i+j < cont) && j < 25 ; j++){
                if(aux != '\n')
                    printf(" %c ", *(char *) aux);
                else
                    printf(" ");
                aux ++;
            }
            printf("\n");
            for(int j=0;(i+j < cont) && j < 25; j++){
                printf("%02X ", *(char *)addr);
                addr ++;
            }
            printf("\n");
        }
    }
    return 0;
}
int cmdMemfill(char* opcion[], int nTrozos, datos* data){
    if(opcion[0] != NULL){
        char *ptr;
        int n = 128;
        int c = 65;
        if(nTrozos >= 3 ) n = atoi(opcion[1]);
        if(nTrozos == 4 ){
            c = atoi(opcion[2]);
        }
        long addr = strtoul(opcion[0],&ptr,16);
        printf("Llenando %d bytes de memoria con el byte %c(%x) a partir de la direccion %s\n", n,
               c + '0'-48, c, opcion[0]);
        for(int i=0;i<n;i++){
            *(int *)addr = c;
            addr ++;
        }
    }
    return 0;
}

void Do_pmap (void) /*sin argumentos*/
{ pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4]={"pmap",elpid,NULL};

    sprintf (elpid,"%d", (int) getpid());
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
    }
    if (pid==0){
        if (execvp(argv[0],argv)==-1)
            perror("cannot execute pmap (linux, solaris)");

        argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;
        if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");

        argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;
        if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");

        argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
        if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");
        exit(1);
    }
    waitpid (pid,NULL,0);
}

int g1=0,g2=0,g3=0;
int cmdMemory(char* opcion[], int nTrozos, datos* data){
    if(opcion[0] != NULL){
        for(int i=0;i<nTrozos-1;i++){
            if(strcmp(opcion[i], "-vars")== 0){
                int x=0,y=0,z=0;
                static int a=0,b=0,c=0;
                printf("Variables locales:\t\t%p, \t%p, \t%p\n", &x, &y, &z);
                printf("Variables globales:\t\t%p, \t%p, \t%p\n", &g1, &g2, &g3);
                printf("Variables estaticas:\t%p, \t%p, \t%p\n", &a, &b, &c);
            }if(strcmp(opcion[i], "-funcs")== 0){
                printf("Funciones programa:\t\t%p, \t%p, \t%p\n", cmdAutores, cmdFecha, cmdCarpeta);
                printf("Funciones libreria:\t\t%p, \t%p, \t%p\n", printf, scanf, strtoul);
            }if(strcmp(opcion[i], "-blocks")== 0){
                list_Allocations(0, data->memoryList);
            }else if(strcmp(opcion[i], "-all")== 0){
                char *input[] = {"-vars","-funcs", "-blocks"};
                cmdMemory(input, 4, data);
            }else if(strcmp(opcion[i], "-pmap")== 0){
                Do_pmap();
            }
        }
    }else{
        char *input[] = {"-vars","-funcs", "-blocks"};
        cmdMemory(input, 4, data);
    }
    return 0;
}

#define TAMANO 2048
void Recursiva (int n)
{
    char automatico[TAMANO];
    static char estatico[TAMANO];

    printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

    if (n>0)
        Recursiva(n-1);
}

int cmdRecurse(char* opcion[], int nTrozos, datos* data){
    if(opcion[0] != NULL){
        int num = atoi(opcion[0]);
        Recursiva(num);
    }
    return 0;
}
