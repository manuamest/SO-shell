/* Jose Manuel Amestoy Lopez: manuel.amestoy@udc.es
 * Lucia Alvarez Garcia: l.alvarezg@udc.es */
#include "list.h"
#include <stdlib.h>
#include <string.h>

bool isEmptyList(tList L) {
    return ((*L).next == LNULL);   // lista vacía si aparte del nodo cabeza no hay más nodos.
}

void createEmptyList(tList *L) {
    tPosL head;
    if(createNode(&head)){
        head->data.number = -1;
        head->next = LNULL;
        *L = head;              // la lista es un nodo cabeza.
    }
}

bool createNode(tPosL *p) {
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;
}

void insertItem(tItemL d, tList *L) {
    tPosL q, r;
    if (createNode(&q)){
        q->data = d;
        q->next = LNULL;
        if(*L == LNULL) {
            *L = q;
        } else {
            for (r = *L; r->next != LNULL; r = r->next);

            r->next = q;        // si hay memoria disponible, inserta el elemento al final de la cola.
        }
    }
}

int endOfList(tPosL p, tList L) {
    return (p->next == LNULL);
}

void updateItem(tItemL d, tPosL p, tList *L) {
    p->data = d;
}

tPosL findItem(tItemL d, tList L) {
    tPosL p;

    for (p = L; (p != LNULL) && (p->data.number != d.number); p = p->next);

    return p;
}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

tPosL first(tList L) {
    return L->next;  // el nodo cabeza está vacío. El primer elemento no vacío está en el segundo nodo
}

tPosL last(tList L) {
    tPosL p;

    for (p = L; p->next != LNULL; p = p->next);

    return p;
}

tPosL previous(tPosL p, tList L) {
    tPosL q;

    if (p == L || p == (*L).next)
        return LNULL;       // el anterior al nodo cabeza es nulo, y el nodo cabeza está vacío así que también devuelve null.
    else {
        for (q = L; q->next != p; q = q->next);
        return q;
    }
}

tPosL next(tPosL p, tList L) { return p->next; }

void deleteAtPosition(tPosL p, tList *L) {
    tPosL q;

    if (p == *L) {
        *L = (*L)->next;        // el primer elemento eliminable de la lista es el posterior al nodo cabeza.
    }
    else if (p->next == LNULL) {        // si el elemento es el último de la lista
        for (q = *L; q->next->next != LNULL; q = q->next);
        q->next = LNULL;
    }
    else {              // si el elemento no está en un extremo de la lista
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }

    free(p);
}

void clearOutList(tList *L) {
    tPosL p;

    while (!isEmptyList(*L)) {
        p = *L;
        *L = (*L)->next;
        free(p);
    }
}