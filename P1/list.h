/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */
#include <stdbool.h>

#define LNULL NULL

typedef char tCommand[1024];

typedef struct tItemL {
    int number;
    tCommand command;
} tItemL;

typedef struct tNode* tPosL;

struct tNode {

    tItemL data;
    tPosL next;

};

typedef tPosL tList;

tList initList();
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