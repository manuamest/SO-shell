/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */
#include <stdbool.h>
#include <time.h>

#define LNULL NULL

typedef char tCommand[1024];

typedef struct tItemL {
    int number;
    tCommand command;
    void* blockAddress;
    size_t blockSize;
    struct tm allocTime;
    int allocType;          // 1 = malloc, 2 = shared, 3 = mapped
    int keySh;
    char fileName[100];
    int fileDescriptor;
} tItemL;

typedef struct tNode* tPosL;

struct tNode {

    tItemL data;
    tPosL next;

};

typedef tPosL tList;

void createEmptyList(tList *L);
bool createNode(tPosL* p);
void insertItem(tItemL d, tList *L);
void updateItem(tItemL d, tPosL p, tList* L);
tPosL findItem(tItemL d,tList L);
bool isEmptyList(tList L);
tItemL getItem(tPosL p, tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL previous(tPosL p, tList L);
tPosL next(tPosL p,tList L);
void deleteAtPosition(tPosL p , tList *L);
void clearOutList(tList *L);